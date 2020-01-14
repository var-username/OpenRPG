var spawn = require('child_process').spawn;
var build;

var os = require('os');
//control OS
//then run command depending on the OS

// ignore 'node' and 'build.js' and get all following args
// these args get passed to the build scripts
var args = process.argv.slice(2);
var OS_TYPE = os.type();

if (args[0] !== 'download') {
    if (OS_TYPE === 'Linux') build = spawn('./build.sh', args);
    else if (OS_TYPE === 'Darwin') build = spawn('./build.sh', args);
    else if (OS_TYPE === 'Windows_NT') build = spawn('build.bat', args);
    else throw new Error('Unsupported OS found: ' + OS_TYPE);

    build.stdout.on('data', (data) => {
        process.stdout.write(data.toString());
    });

    build.stderr.on('data', (data) => {
        process.stderr.write(data.toString());
    });

    build.on('exit', (code) => {
        console.log('child process exited with code ' + code.toString());
    });
} else {
    /**
     * TODO(incomingstick): Clean this up and functionize it where we can. I threw this together to get it working, so
     * by no means is it perfect.
     */
    const fs = require('fs');
    var tmpdir = os.tmpdir();

    // make the tmpdir if it doesn't exist
    if (!fs.existsSync(tmpdir)) {
        fs.mkdirSync(tmpdir);
    }

    // if the tmpdir still doesn't exist, lets try it locally
    if (!fs.existsSync(tmpdir)) {
        tmpdir = './';
    }

    var repo = require('./package.json')
        .repository.url.replace('git+', '')
        .replace('OpenRPG.git', 'OpenRPG');
    var ver = require('./package.json').version;
    var ext = '.tar.gz';

    var osName;

    if (OS_TYPE === 'Windows_NT') osName = 'win64';
    else if (OS_TYPE === 'Linux' || OS_TYPE === 'Darwin') osName = OS_TYPE;
    else throw new Error('Unsupported OS found: ' + OS_TYPE);

    const path = require('path');

    var target = '';
    var targetVer = '';

    var loadMainPackageJSON = (attempts) => {
        attempts = attempts || 1;
        if (attempts > 5) {
            throw new Error("Can't resolve main package.json file");
        }
        var mainPath = attempts === 4 ? './' : Array(attempts).join('../');
        try {
            return require.main.require(mainPath + 'package.json');
        } catch (e) {
            return loadMainPackageJSON(++attempts);
        }
    };

    var parentPackageJSON = loadMainPackageJSON();

    var depVer = parentPackageJSON.dependencies.electron;
    var devDepVer = parentPackageJSON.devDependencies.electron;

    target = 'electron';
    targetVer = depVer !== undefined ? depVer : devDepVer;

    if (targetVer === undefined) {
        target = 'node';
        targetVer = process.version;
    }

    var targetString = '-' + target + '-' + targetVer.replace(/[\^\<\>\=v]/g, '');
    var base = 'OpenRPG-' + ver + targetString + '-' + osName;
    var filename = base + ext;
    var gitURL = repo + '/releases' + '/download' + '/v' + ver + '/' + filename;
    var shaExt = '.sha512';

    var download = path.join(tmpdir, filename);

    const https = require('https');
    const url = require('url');
    const crypto = require('crypto');

    var file = fs.createWriteStream(download);
    const downloadTarball = (tarURL) => {
        var checksum;

        console.log('Fetching Checksum...\t', tarURL + shaExt);
        https
            .get(tarURL + shaExt, (response) => {
                const getSha = (data) => {
                    let mem = '';

                    data.on('data', (chunk) => {
                        mem += chunk;
                    });

                    data.on('end', () => {
                        checksum = mem.split(' ', 1)[0];
                    });
                };

                if (response.statusCode > 300 && response.statusCode < 400 && response.headers.location) {
                    if (url.parse(response.headers.location).hostname) {
                        https.get(response.headers.location, (sha) => {
                            getSha(sha);
                        });
                    } else {
                        https.get(url.resolve(url.parse(url).hostname, response.headers.location), (sha) => {
                            getSha(sha);
                        });
                    }
                } else {
                    // We were given a response.statusCode < 300 || response.statusCode > 400
                    switch (response.statusCode) {
                        case 404: {
                            console.log('Error 404 URL Not Found:', tarURL + shaExt);

                            if (target === 'electron') {
                                target = 'node';
                                targetVer = process.version;
                                targetString = '-' + target + '-' + targetVer.replace(/[\^\<\>\=v]/g, '');
                            } else if (target === 'node') {
                                target = 'core';
                                targetVer = ver;
                                targetString = '';
                            } else
                                break;

                            base = 'OpenRPG-' + ver + targetString + '-' + osName;
                            filename = base + ext;
                            gitURL = repo + '/releases' + '/download' + '/v' + ver + '/' + filename;

                            console.log('Falling back to:\t', gitURL);
                            downloadTarball(gitURL);

                            break;
                        }
                    }
                }
            })
            .on('close', () => {
                console.log('Downloading GZip...\t', tarURL);
                https
                    .get(tarURL, (response) => {
                        // TODO sha256 check the download before writing
                        const getTarball = (tarball) => {
                            const sha512 = crypto.createHash('sha512');
                            sha512.setEncoding('hex');

                            tarball.on('end', () => {
                                sha512.end();

                                const hex = sha512.read();

                                if (hex !== checksum) {
                                    console.log('hex\t', hex);
                                    console.log('checksum', checksum);
                                    fs.unlinkSync(download);
                                    throw new Error('Checksum failed!');
                                } else console.log('Checksum passed!');
                            });

                            tarball.pipe(file);
                            tarball.pipe(sha512);
                        };

                        if (response.statusCode > 300 && response.statusCode < 400 && response.headers.location) {
                            if (url.parse(response.headers.location).hostname) {
                                https.get(response.headers.location, (tarball) => {
                                    getTarball(tarball);
                                });
                            } else {
                                https.get(
                                    url.resolve(url.parse(url).hostname, response.headers.location),
                                    (tarball) => {
                                        getTarball(tarball);
                                    }
                                );
                            }
                        } else {
                            // We were given a response.statusCode < 300 || response.statusCode > 400
                            switch (response.statusCode) {
                                case 404: {
                                    console.log('Error 404 URL Not Found:', tarURL);

                                    if (target === 'electron') {
                                        target = 'node';
                                        targetVer = process.version;
                                        targetString = '-' + target + '-' + targetVer.replace(/[\^\<\>\=v]/g, '');
                                    } else if (target === 'node') {
                                        target = 'core';
                                        targetVer = ver;
                                        targetString = '';
                                    } else
                                        break;

                                    base = 'OpenRPG-' + ver + targetString + '-' + osName;
                                    filename = base + ext;
                                    gitURL = repo + '/releases' + '/download' + '/v' + ver + '/' + filename;

                                    console.log('Falling back to:\t', gitURL);
                                    downloadTarball(gitURL);

                                    break;
                                }
                            }
                        }
                    })
                    .on('error', (error) => {
                        console.error(error);
                    });
            })
            .on('error', (error) => {
                console.error(error);
            });
    };

    file.on('open', () => {
        downloadTarball(gitURL);
    });

    file.on('finish', () => {
        const tar = require('tar');

        console.log('Unzipping...\t\t', download);
        tar.extract({
            cwd: tmpdir,
            file: file.path,
            sync: true
        });

        let uncomp = path.join(tmpdir, base);
        var dist = path.join(__dirname, 'dist');

        const mv = require('mv');
        if (fs.existsSync(dist)) fs.rmdirSync(dist, { recursive: true });
        if (fs.existsSync(uncomp))
            mv(uncomp, dist, (error) => {
                if (error) throw error;
            });

        console.log(file.path, '->', dist);

        fs.unlinkSync(file.path);
    });
}
