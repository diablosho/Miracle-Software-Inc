namespace AtimsWeb.Models
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    public partial class AppAO_SubModule
    {
        [Key]
        [Required]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int AppAO_SubModule_id { get; set; }

        [Required]
        public int AppAO_Module_id { get; set; }

        [Required]
        [StringLength(50)]
        public string AppAO_SubModule_Name { get; set; }

        [StringLength(50)]
        public string AppAO_SubModule_usercontrol { get; set; }

        [Required]
        public int? AppAO_SubModule_visible { get; set; }

        public int AppAO_SubModule_order { get; set; }

        [StringLength(150)]
        public string AppAO_SubModule_ToolTip { get; set; }

        public int? AppAO_SubModule_DetailFlag { get; set; }

        [StringLength(250)]
        public string AppAO_SubModule_Help { get; set; }

        [StringLength(16)]
        public string AppAO_SubModule_AddOn_LicenseKey { get; set; }

        public int? AppAO_SubModule_AddOn_Flag { get; set; }

        [ForeignKey("AppAO_Module_id")]
        public virtual AppAO_Module AppAO_Module { get; set; }

    }
}
