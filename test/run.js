var b64pack = require('../build/Release/b64pack');

b64pack.compress('This is a test string.', function(err, result) {
    console.log(result);
});
