var cordova = require('cordova');

var UbilibPlugin = function() {};

UbilibPlugin.prototype.getParams = function (success, error, arg) {
    cordova.exec(success, error, 'UbilibPlugin', 'getParams', [arg]);
};
UbilibPlugin.prototype.fft = function (success, error, arg) {
    cordova.exec(success, error, 'UbilibPlugin', 'fft', [arg]);
};
UbilibPlugin.prototype.getParams2 = function (success, error, arg) {
    cordova.exec(success, error, 'UbilibPlugin', 'getParams2', [arg]);
};
var ubilibPlugin = new UbilibPlugin();
module.exports = ubilibPlugin;