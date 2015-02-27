namespace AtimsWeb.Models
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;

    /* NOTE: THIS CLASS WAS AUTO GENERATED
     *   Please triple check this class, as well as its entry in ~/Models/JMS.cs
     *   to ensure that it is using the proper tags, relationships, and function
     *   calls.
     */

    public partial class Housing_Unit
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int Housing_unit_id { get; set; }

        public int? Facility_id { get; set; }

        [StringLength(8)]
        public string housing_unit_location { get; set; }

        public int? housing_unit_capacity { get; set; }

        [StringLength(8)]
        public string housing_unit_number { get; set; }

        [StringLength(6)]
        public string housing_unit_bed_number { get; set; }

        [StringLength(6)]
        public string housing_unit_bed_location { get; set; }

        public int? housing_unit_juvenile_flag { get; set; }

        public DateTime? create_date { get; set; }

        public DateTime? update_date { get; set; }

        public int? housing_unit_sex { get; set; }

        public int? Housing_Unit_Floor { get; set; }

        public int? Housing_Unit_Offsite { get; set; }

        public int? Housing_Unit_Medical { get; set; }

        public int? Housing_Unit_Mental { get; set; }

        public int? Housing_Unit_VisitAllow { get; set; }

        public int? Housing_Unit_Holding { get; set; }

        public int? Housing_Unit_Inactive { get; set; }

        public int? Housing_Unit_CommAllow { get; set; }

        public int? housing_unit_actual_capacity { get; set; }

        public int? housing_unit_out_of_service { get; set; }

        public int? housing_unit_rated_capacity { get; set; }

        [StringLength(1500)]
        public string housing_unit_out_of_service_note { get; set; }

        public int? housing_unit_out_of_service_by { get; set; }

        public DateTime? housing_unit_out_of_service_date { get; set; }

        [Column("Housing_Unit_Out_of_service_reason ")]
        [StringLength(150)]
        public string Housing_Unit_Out_of_service_reason_ { get; set; }

        public int? housing_unit_DoNotRecommend { get; set; }

        [StringLength(1500)]
        public string housing_unit_ClassifyRecString { get; set; }
    }
}
