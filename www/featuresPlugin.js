var cordova = require('cordova');

var FeaturesPlugin = function() {};

FeaturesPlugin.prototype.getParams = function (success, error, arg) {
    cordova.exec(success, error, 'FeaturesPlugin', 'getParams', [arg]);
};
FeaturesPlugin.prototype.fft = function (success, error, arg) {
    cordova.exec(success, error, 'FeaturesPlugin', 'fft', [arg]);
};
FeaturesPlugin.prototype.getParams2 = function (success, error, arg) {
    cordova.exec(success, error, 'FeaturesPlugin', 'getParams2', [arg]);
};
var featuresPlugin = new FeaturesPlugin();
module.exports = featuresPlugin;