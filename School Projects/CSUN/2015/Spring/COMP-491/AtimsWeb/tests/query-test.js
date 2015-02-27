// Main Controller
var queryTestController = function ($scope, $http, $rootScope, $location) {
    
    $scope.info = "..loading..";

    $http.get("../api/Modules/4")
        .success(function (data) { setupModules(data) })
        .error(function (data) { loadAppFailed(data) });
    var setupModules = function (data) {
        var modules = angular.fromJson(data);
        console.log( modules );
        $scope.info = modules[0];
    };
    var loadAppFailed = function (data) {
        $scope.info = "Failed."
    };

};
queryTestController.$inject = ['$scope','$http','$rootScope','$location'];

// App Declaration
var queryTestApp = angular.module('queryTestApp', []);
queryTestApp.controller('QueryTestController', queryTestController);
