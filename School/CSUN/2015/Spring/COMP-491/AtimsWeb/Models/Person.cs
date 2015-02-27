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

    [Table("Person")]
    public partial class Person
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int person_id { get; set; }

        [StringLength(50)]
        public string person_first_name { get; set; }

        [StringLength(50)]
        public string person_middle_name { get; set; }

        [StringLength(50)]
        public string person_last_name { get; set; }

        [StringLength(50)]
        public string person_phone { get; set; }

        [StringLength(50)]
        public string person_business_phone { get; set; }

        [StringLength(50)]
        public string person_business_fax { get; set; }

        public DateTime? person_dob { get; set; }

        [StringLength(50)]
        public string person_place_of_birth { get; set; }

        [StringLength(50)]
        public string person_dl_number { get; set; }

        [StringLength(50)]
        public string person_dl_State { get; set; }

        [StringLength(50)]
        public string person_dl_class { get; set; }

        public DateTime? person_dl_expiration { get; set; }

        [StringLength(50)]
        public string person_other_id_type { get; set; }

        [StringLength(50)]
        public string person_other_id_number { get; set; }

        [StringLength(50)]
        public string person_other_id_state { get; set; }

        public DateTime? person_other_id_expiration { get; set; }

        [StringLength(50)]
        public string person_ssn { get; set; }

        public int? person_contact_id { get; set; }

        [StringLength(50)]
        public string person_contact_relationship { get; set; }

        public short? person_age { get; set; }

        [StringLength(50)]
        public string person_suffix { get; set; }

        [StringLength(50)]
        public string person_site_id { get; set; }

        [StringLength(50)]
        public string person_site_bnum { get; set; }

        [StringLength(50)]
        public string person_fbi_no { get; set; }

        [StringLength(10)]
        public string person_deceased { get; set; }

        public DateTime? person_deceased_date { get; set; }

        [StringLength(10)]
        public string person_missing { get; set; }

        public DateTime? person_missing_date { get; set; }

        [StringLength(50)]
        public string person_maiden_name { get; set; }

        [StringLength(50)]
        public string person_number { get; set; }

        public DateTime? create_date { get; set; }

        public DateTime? update_date { get; set; }

        public int? person_duplicate_id { get; set; }

        [StringLength(50)]
        public string person_phone_2 { get; set; }

        [StringLength(50)]
        public string person_cell_phone { get; set; }

        [StringLength(200)]
        public string person_email { get; set; }

        [StringLength(500)]
        public string person_notes { get; set; }

        [StringLength(50)]
        public string person_cii { get; set; }

        [StringLength(50)]
        public string person_alien_no { get; set; }

        [StringLength(100)]
        public string person_place_of_birth_list { get; set; }

        [StringLength(50)]
        public string person_doc { get; set; }

        public int? person_dl_no_expiration { get; set; }

        [StringLength(20)]
        public string person_fpc_number { get; set; }

        [StringLength(50)]
        public string person_caution_flag { get; set; }

        public int? person_sex_last { get; set; }

        public int? person_race_last { get; set; }

        public int? person_height_primary_last { get; set; }

        public int? person_weight_last { get; set; }

        public int? person_hair_color_last { get; set; }

        public int? person_eye_color_last { get; set; }

        public int? person_height_secondary_last { get; set; }

        public int? person_height_inch_last { get; set; }

        [StringLength(50)]
        public string person_fcn_number { get; set; }

        public int? person_illegal_alien { get; set; }

        [StringLength(50)]
        public string FKN_last_name { get; set; }

        [StringLength(50)]
        public string FKN_first_name { get; set; }

        [StringLength(50)]
        public string FKN_middle_name { get; set; }

        [StringLength(50)]
        public string FKN_suffix_name { get; set; }

        public int? person_us_citizen { get; set; }

        public int? Person_Fingerprint_id { get; set; }

        [StringLength(50)]
        public string Person_Fingerprint_Image_Path { get; set; }

        [StringLength(50)]
        public string AFIS_Number { get; set; }

        public int? create_by { get; set; }

        public int? update_by { get; set; }

        public int? Vendor_Client_id { get; set; }
    }
}
