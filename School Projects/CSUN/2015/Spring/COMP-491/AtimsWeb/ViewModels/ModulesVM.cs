using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using AtimsWeb.Models;

namespace AtimsWeb.ViewModels {
    public class ModulesVM {
        public string Name;
        public string ToolTip;
        public List<SubModuleVM> SubModules;
    }
}