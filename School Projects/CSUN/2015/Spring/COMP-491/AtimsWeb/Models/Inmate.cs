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

    [Table("Inmate")]
    public partial class Inmate
    {
        [Key]
        [Column(Order = 0)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int inmate_id { get; set; }

        [Key]
        [Column(Order = 1)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int person_id { get; set; }

        public int? housing_unit_id { get; set; }

        [Key]
        [Column(Order = 2)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int Facility_id { get; set; }

        [StringLength(50)]
        public string inmate_security_level { get; set; }

        [Key]
        [Column(Order = 3)]
        [StringLength(50)]
        public string inmate_number { get; set; }

        [Key]
        [Column(Order = 4)]
        public DateTime inmate_received_date { get; set; }

        [StringLength(50)]
        public string inmate_status { get; set; }

        [StringLength(50)]
        public string inmate_wristband_id { get; set; }

        public DateTime? inmate_scheduled_release_date { get; set; }

        public int? inmate_officer_id { get; set; }

        [StringLength(50)]
        public string inmate_contract_housing { get; set; }

        [StringLength(10)]
        public string inmate_footlocker { get; set; }

        [StringLength(20)]
        public string inmate_site_number { get; set; }

        [Key]
        [Column(Order = 5)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int inmate_juvenile_flag { get; set; }

        [Key]
        [Column(Order = 6)]
        public DateTime create_date { get; set; }

        [Key]
        [Column(Order = 7)]
        public DateTime update_date { get; set; }

        public int? inmate_classification_id { get; set; }

        [StringLength(50)]
        public string inmate_personal_inventory { get; set; }

        [StringLength(50)]
        public string inmate_Current_Track { get; set; }

        [Column(TypeName = "money")]
        public decimal? inmate_balance { get; set; }

        [Column(TypeName = "money")]
        public decimal? inmate_deposited_balance { get; set; }

        [Column(TypeName = "money")]
        public decimal? inmate_debt { get; set; }

        [Key]
        [Column(Order = 8)]
        [StringLength(50)]
        public string inmate_medical_flags { get; set; }

        [Key]
        [Column(Order = 9)]
        [StringLength(50)]
        public string inmate_class_flags { get; set; }

        public int? Work_Crew_id { get; set; }

        [Key]
        [Column(Order = 10)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int inmate_active { get; set; }

        [StringLength(10)]
        public string Phone_Pin { get; set; }

        public DateTime? last_review_date { get; set; }

        public int? last_review_by { get; set; }

        public DateTime? Last_Class_Review_Date { get; set; }

        public int? Last_Class_Review_By { get; set; }

        [StringLength(150)]
        public string supply_shirt { get; set; }

        [StringLength(150)]
        public string supply_pants { get; set; }

        [StringLength(150)]
        public string supply_shoes { get; set; }

        [StringLength(150)]
        public string supply_underwear { get; set; }

        [StringLength(150)]
        public string supply_bra { get; set; }

        public int? Special_ClassQueue_Interval { get; set; }
    }
}
