/// <reference path="../../../../../../App.Web/scripts/app/home/datecontrol.js" />
/// <reference path="../../../../../_PublishedWebsites\App.Web/scripts/app/home/datecontrol.js" />

describe('Controller: TestMainCtrl', function () {
    beforeEach(module('AtimsWeb'));
    var TestMainCtrl, scope;
    beforeEach(inject(function ($controller) {
        scope = {};
        TestMainCtrl = $controller('TestMainCtrl', {
            $scope: scope
        });
    }));
    it('should have scope defined', function () {
        expect(scope).toBeDefined();
    });
});