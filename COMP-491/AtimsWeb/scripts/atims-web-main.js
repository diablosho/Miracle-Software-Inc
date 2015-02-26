// Main Controller
var atimsAppController = function ($scope, $http, $rootScope, $location) {
    //// Variables

    /// Web Page
    // HTML Page Title
    $scope.pageTitle = "Atims JMS";
    /// Modules
    // $scope.moduleNameMap is a HashTable that maps the name (AppAO_Module_Name)
    //   of each loaded module to the javascript module object. This is primarly
    //   used for URL and page routing.
    $scope.moduleNameMap = {};
    // $scope.moduleMenu is the list of all loaded modules which are set to be visible
    //   (AppAO_Module_visible = 1). This is directly linked using ng-repeat in
    //   the index.html file for displaying the top menu.
    $scope.moduleMenu = [];
    //  $scope.subModuleMenu is the list of all loaded subModules for the currently
    //   selected module. Generally, this is both set from and should be the same
    //   value as $scope.selectedModule.subModuleMenu. However, this is intentionally
    //   kept separate for when pages that need to be displayed are not linked to a
    //   subModule and the lefthand menu must represent that. This is directly linked
    //   using ng-repeat in the index.html file for displaying the left menu.
    $scope.subModuleMenu = [];
    
    /// Current Page / URL Handling
    //   The current page is based off of three key values: the current app, the
    //     current module, and the current subModule. While it is possible to load
    //     other pages using displayPage( url ), this is not the normal behavior. 
    //     Currently, the only app being implemented is the JMS, whose id is 4.
    //   When either a URL is entered, or a link is clicked, the function
    //     goToSubModule( moduleName, subModuleName) is called and the name of the
    //     module and subModule are checked against the name map hashtables. The
    //     actual page is displayed using ng-include with the link retrieved from
    //     the database stored in each subModule.
    // $scope.selectedAppId is used to select modules based on which "app" is being
    //   presented. This value is determined from the AppAO_Module.AppAO_id column,
    //   and is parsed server side through the API to prevent unecessary modules from
    //   being sent to the browser.
    $scope.selectedAppId = -1;
    // $scope.selectedModule is the currently selected module object
    $scope.selectedModule = null;
    // $scope.selectedSubModule is the currently selected subModule object
    $scope.selectedSubModule = null;
    // $scope.page is the currently selected page. In the general case, this value
    //   is set using goToSubModule instead of displayPage to ensure the correct
    //   subModule menu is displayed. Setting this directly or using displayPage
    //   will NOT update the menu, but will allow any page to be displayed embedded
    //   including those not linked to a subModule. In the general case, this
    //   value is set to $scope.selectedSubModule.link
    $scope.page = "";


    //// App / Module and SubModule Loading Functions
    
    /// Loading the App
    // $scope.loadApp cleans the page and then starts to load the set of modules
    //   and subModuels associated with the app id (AppAO_Module.AppAO_id). Currently
    //   only JMS (AppAO_id = 4) is being implemented.
    //   @TODO: This may need to change to load by name once other apps are being
    //     implemented. See $scope.goToApp(id) below.
    var loadApp = function( appId ){
        // Clear variables for loading the new app
        $scope.moduleNameMap = {};
        $scope.moduleMenu = [];
        $scope.subModuleMenu = [];
        $scope.selectedAppId = appId;
        $scope.selectedModule = null;
        $scope.selectedSubModule = null;
        $scope.page = "";
        // This makes a request using $http.get to the server for the modules
        //   associated with app based on $scope.appId. Since the response is not
        //   immediate, we should display the loading screen.
        $scope.appLoaderShow( true );
        $http.get("api/Modules/" + $scope.selectedAppId)
            .success(function (data) { setupModules(data) })
            .error(function (data) { loadAppFailed(data) });
    };
    // loadAppFailed(data) is called when the $http function returns an error code.
    //   This is not intended to catch exceptions, which should bubble to the console.
    //   @TODO: Failure Handling (maybe go to 404 page?)
    var loadAppFailed = function( data ){
        // @TODO: I do nothing, someone fix me :D
        console.log( "Module HTTP Request Failed: " + data );
    };
    // setupModules is called from a successful $http.get request in loadApp, and
    //   will attempt to load the modules and subModules from the recieved Json data
    var setupModules = function (data) {
        // Load all Modules and SubModules
        //   Json Parse
        var rawMenuList = angular.fromJson(data);
        //   For each module:
        //     Add each module to moduleNameMap, and if visible to $scope.moduleMenu.
        //     Add variables for subModuleMenu and subModuleNameMap arrays.
        //     Populate subModuleMenu and subModuleNameMap for each child subModule.
        for (var i = 0; i < rawMenuList.length; i++) {
            var module = rawMenuList[i];
            module.subModuleMenu = [];
            module.subModuleNameMap = {};
            $scope.moduleNameMap[module.Name] = module;
            $scope.moduleMenu.push(module);
            // Add each subModule to its parent's subModuleNameMap, and if visible
            //   to its parent's subModuleMenu.
            for (var j = 0; j < module.SubModules.length; j++) {
                var subModule = module.SubModules[j];
                module.subModuleMenu.push(subModule);
                module.subModuleNameMap[subModule.Name] = subModule;
            }
        }
        // At this point: App, Modules, and SubModules have been successfully loaded
        //   @TODO: Implement individual app home pages
        urlChangeEvent(null);
        //   Ensure webpage is snapped in place
        resizeHandler();
        //   Hide loading screen and show website
        $scope.appLoaderShow(false);
    };


    //// Current Page / URL Handling
    // @TODO: Implement a 404 page (See display404() function below -- it's empty)
    // @TODO: Implement automatic homepage based on User Preferences (See displayHome() below)

    /// Current Page
    // displayPage attempts to load a new page into the ng-include
    var displayPage = function (newPage) {
        // Check if the requested page is already loaded, and set the page to
        //   null first. If you *only* set the page to the same value, angular
        //   will assume the page is the same and does not need to be reloaded.
        if ($scope.page ==  newPage) {
            $scope.page = "";
        }
        $scope.page = newPage;
    };
    // displaySubModule(moduleName, subModuleName) attempts to find and load the
    //   module/subModule pair into the menu's, and then passes the subModules
    //   link to displayPage
    var displaySubModule = function (moduleName, subModuleName) {
        // Module
        //   Find the requested module, and check if it exists
        var module = $scope.moduleNameMap[moduleName];
        if (module == undefined) {
            display404("Module not found: " + moduleName);
            return;
        }
        //   If exists, set it to current
        $scope.selectedModule = module;

        // SubModule
        //   Find the requested subModule, and check if it exists
        var subModule = module.subModuleNameMap[subModuleName]
        if (subModule == undefined) {
            display404("SubModule not found: " + moduleName + "/" + subModuleName);
            return;
        }
        //   If exists, set it to current
        $scope.selectedSubModule = subModule;

        // Try to go to the subModule's page
        $scope.selectedSubModule.Usercontrol = $scope.selectedSubModule.Usercontrol ||
            "Views/" + encodeURI(moduleName) + "/" + encodeURI(subModuleName) + ".html";
        displayPage($scope.selectedSubModule.Usercontrol);
    };
    // Displays the users personal home page
    //   @ TODO: Implement once users are implemented
    var displayHome = function (){
        // @TODO: I do the wrong thing, someone fix me :D
        displayPage( "Views/Home.cshtml" );
    };
    // Displays the 404 error page
    //   @ TODO: Implement this (See above - No 404 page exists as of writing this)
    var display404 = function (errorInfo){
        // @TODO: I do nothing, someone fix me :D
        console.log( errorInfo );
    };
    // $scope.pageLoaded() is called after $scope.page has been successfully loaded
    //   with ng-include
    $scope.pageLoaded = function (){
        // @TODO: I do nothing, someone fix me :D
    };
    
    /// URL Handling
    // goToSubModule(moduleName, subModuleName) is used inside the web pages for link
    //   urls. This is equivalent to href="#/moduleName/subModuleName/"
    $scope.goToSubModule = function (moduleName, subModuleName){
        $location.path("/" + moduleName + "/" + subModuleName);
    };
    // goToPath(path) is used inside the web pages to set the url directly, instead of
    //   using goToSubModule to format it. This can also allow URL's that do not follow
    //   the URL convention.
    $scope.goToPath = function(path){
        $location.path( path );
    };
    // goToApp(appID) is currently not in use as only the JMS (AppAO_id = 4) is being implemented
    //    @TODO: This may need to change to by name instead of id when the time comes
    $scope.goToApp = function (id){
        $scope.appLoaderShow( true );
        loadApp(id);
    };
    // urlChangeEvent(event) is called every time the browser url is changed. 
    var urlChangeEvent = function (event){
        // Wait until we're loaded (it will call urlChangeEvent anyways)
        if( $scope.moduleMenu.length == 0 )
            return;

        var rawpath = $location.path();
        // Matches "" "#" and "#/" which should all lead to the users home page
        if( rawpath.match( /^#?\/?$/ ) ){
            displayHome();
        }else{
            var path = $location.path().split('/');
            displaySubModule(path[1], path[2]);
        }
    };
    // This links the event and function for when the URL has changed.
    $scope.$on('$locationChangeSuccess', urlChangeEvent);


    //// Window Styling - CSS Synergy
    // @TODO: Implement CSS changes for highlighting current module
    //    (see index.html for subModule highlighting)
    // SubModule Menu Toggle
    $scope.menuToggleText = "<<";
    $scope.menuToggle = function ( ){
        $("#wrapper").toggleClass("toggled");
        $scope.menuToggleText = ($scope.menuToggleText === "<<")? ">>" : "<<";
    };
    // Shows or Hides the full page loading screen
    $scope.appLoaderShow = function (toShow) {
        if ($("#loading").hasClass("toggled") === toShow  ) {
            $("#loading").toggleClass("toggled");
            $("#loading-hider").toggleClass("toggled");
        }
    };
    // Window Resize Fixed Position Handler
    var resizeHandler = function () {
        // Get navbar-over and navbar-under
        var navbarOver = $(".navbar-over");
        // Get bottom of navbarOver
        var navbarUnder = $(".navbar-under");
        // Set navbar-under flush against navbar-over
        navbarUnder.css("top", navbarOver.offset().top + navbarOver.outerHeight() + "px");
        // Set wrapper flush against navbarUnder
        $("#wrapper").css("top", ( navbarUnder.offset().top + navbarUnder.outerHeight() ) + "px");
    };
    $(window).resize(resizeHandler);


    //// Default Behavior
    // Load JMS App (AppAO_id = 4)
    loadApp(4);
};
atimsAppController.$inject = ['$scope','$http','$rootScope','$location'];

// App Declaration
var atimsMainApp = angular.module('atimsMainApp', []);
atimsMainApp.controller('AtimsAppController', atimsAppController);