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

    [Table("Arrest")]
    public partial class Arrest
    {
        [Key]
        [Column(Order = 0)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int arrest_id { get; set; }

        public int? probation_id { get; set; }

        public int? suspect_id { get; set; }

        [Key]
        [Column(Order = 1)]
        [StringLength(40)]
        public string arrest_booking_no { get; set; }

        [Key]
        [Column(Order = 2)]
        [StringLength(10)]
        public string arrest_type { get; set; }

        [StringLength(12)]
        public string arrest_ucr_number { get; set; }

        [StringLength(1)]
        public string arrest_ucr_transaction_type { get; set; }

        [Key]
        [Column(Order = 3)]
        public DateTime arrest_date { get; set; }

        [StringLength(1)]
        public string arrest_multiple_segment_indicator { get; set; }

        [StringLength(3)]
        public string arrest_ucr_code { get; set; }

        [StringLength(1)]
        public string arrest_fingerprint_by_DOJ { get; set; }

        [Key]
        [Column(Order = 4)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int arresting_agency_id { get; set; }

        [Key]
        [Column(Order = 5)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int booking_agency_id { get; set; }

        public int? arrest_sentenced { get; set; }

        [StringLength(50)]
        public string arrest_law_enforcement_disposition { get; set; }

        [StringLength(50)]
        public string arrest_last_time_in_custody { get; set; }

        [StringLength(50)]
        public string arrest_last_time_location { get; set; }

        [StringLength(50)]
        public string arrest_last_time_crime { get; set; }

        public DateTime? arrest_arraignment_date { get; set; }

        public int? arrest_booking_supervisor_id { get; set; }

        public int? arrest_probation_officer_id { get; set; }

        public int? arrest_parole_officer_id { get; set; }

        [Key]
        [Column(Order = 6)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int arrest_booking_officer_id { get; set; }

        [Key]
        [Column(Order = 7)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int arrest_officer_id { get; set; }

        [Key]
        [Column(Order = 8)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int arrest_receiving_officer_id { get; set; }

        [Key]
        [Column(Order = 9)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int arrest_transporting_officer_id { get; set; }

        public int? arrest_search_officer_id { get; set; }

        [Key]
        [Column(Order = 10)]
        [StringLength(150)]
        public string arrest_location { get; set; }

        public DateTime? arrest_sentence_start_date { get; set; }

        [StringLength(10)]
        public string arrest_sentence_by_hour { get; set; }

        public int? arrest_gw_gt { get; set; }

        public int? arrest_time_served_days { get; set; }

        public int? arrest_sentence_group { get; set; }

        public int? arrest_arraignment_court_id { get; set; }

        [StringLength(10)]
        public string arrest_arraignment_flag { get; set; }

        [StringLength(10)]
        public string arrest_charges_filed_flag { get; set; }

        public DateTime? arrest_charges_filed_date { get; set; }

        [StringLength(500)]
        public string arrest_court_docket { get; set; }

        public int? arrest_court_jurisdiction_id { get; set; }

        [StringLength(50)]
        public string arrest_sentence_findings { get; set; }

        [StringLength(50)]
        public string arrest_sentence_type { get; set; }

        [StringLength(1500)]
        public string arrest_sentence_description { get; set; }

        [StringLength(150)]
        public string arrest_conditions_of_release { get; set; }

        public int? arrest_sentence_fine_days { get; set; }

        [StringLength(50)]
        public string arrest_non_compliance { get; set; }

        public DateTime? arrest_charges_when_filed { get; set; }

        public int? arrest_sentence_judge_id { get; set; }

        [StringLength(20)]
        public string arrest_site_booking_no { get; set; }

        [Key]
        [Column(Order = 11)]
        public DateTime arrest_booking_date { get; set; }

        [StringLength(50)]
        public string arrest_pcn { get; set; }

        [StringLength(10)]
        public string arrest_reactivate { get; set; }

        public int? arrest_booking_status { get; set; }

        public int? arrest_juvenile_flag { get; set; }

        [Key]
        [Column(Order = 12)]
        public DateTime create_date { get; set; }

        [Key]
        [Column(Order = 13)]
        public DateTime update_date { get; set; }

        [StringLength(50)]
        public string arrest_juvenile_disposition { get; set; }

        [StringLength(50)]
        public string arrest_law_disposition_turnover { get; set; }

        [StringLength(1500)]
        public string arrest_notes { get; set; }

        public int? arrest_billing_agency_id { get; set; }

        public int? arrest_delete_flag { get; set; }

        public int? agency_billing_exception_flag { get; set; }

        public DateTime? arrest_sentence_release_date { get; set; }

        public int? arrest_sentence_gw_gt_days { get; set; }

        public int? arrest_sentence_days { get; set; }

        public int? arrest_sentence_hours { get; set; }

        public int? arrest_sentence_weekender { get; set; }

        public int? arrest_sentence_gt_days { get; set; }

        public int? arrest_sentence_wt_days { get; set; }

        public int? arrest_sentence_days_stayed { get; set; }

        public int? arrest_time_served_days_presentence { get; set; }

        public int? arrest_time_served_days_gtwtOther { get; set; }

        public int? arrest_sentence_forthwith { get; set; }

        public int? arrest_sentence_Penal_Institution { get; set; }

        public DateTime? arrest_sentence_Parole_Date { get; set; }

        public int? arrest_sentence_early_release { get; set; }

        public DateTime? arrest_sentence_weekender_return { get; set; }

        public int? arrest_examine_booking { get; set; }

        public int? arrest_sentence_gw_gt_adjust { get; set; }

        public int? arrest_sup_seq_number { get; set; }

        [StringLength(50)]
        public string arrest_case_number { get; set; }

        [StringLength(100)]
        public string arrest_officer_text { get; set; }

        public int? arrest_sentence_consecutive_to { get; set; }

        public DateTime? arrest_sentence_expiration_date { get; set; }

        [Column(TypeName = "money")]
        public decimal? arrest_sentence_fine_amount { get; set; }

        [Column(TypeName = "money")]
        public decimal? arrest_sentence_fine_per_day { get; set; }

        public int? arrest_sentence_amended { get; set; }

        public int? arrest_sentence_manual { get; set; }

        public int? arrest_sentence_override { get; set; }

        public int? arrest_sentence_days_to_serve { get; set; }

        public int? arrest_sentence_actual_days_to_serve { get; set; }

        public DateTime? arrest_sentence_date_info { get; set; }

        public int? arrest_sentence_early_release_40186 { get; set; }

        public int? arrest_sentence_early_release_40241 { get; set; }

        [StringLength(50)]
        public string arrest_sentence_days_interval { get; set; }

        public int? arrest_sentence_days_amount { get; set; }

        public int? arrest_sentence_anytime_release { get; set; }

        public int? arrest_sentence_consecutive_flag { get; set; }

        public int? arrest_release_cleared_id { get; set; }

        public int? arrest_release_cleared_by { get; set; }

        public DateTime? arrest_release_cleared_date { get; set; }

        public int? arrest_active { get; set; }

        public int? arrest_sentence_options_rec { get; set; }

        public int? arrest_intake_complete_flag { get; set; }

        [StringLength(100)]
        public string arrest_transporting_officer_text { get; set; }

        [Column(TypeName = "money")]
        public decimal? bail_amount { get; set; }

        public int? bail_no_bail_flag { get; set; }

        [StringLength(50)]
        public string bail_type { get; set; }

        public int? bail_percent_posted { get; set; }

        [StringLength(50)]
        public string bail_receipt_number { get; set; }

        [StringLength(50)]
        public string arrest_crime_code_type { get; set; }

        [StringLength(50)]
        public string bail_posted_by { get; set; }

        public int? Seal_Flag { get; set; }

        public int? arrest_sentence_gw_gt_factor { get; set; }

        [Key]
        [Column(Order = 14)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int Inmate_ID { get; set; }

        public int? Booking_Complete_Flag { get; set; }

        public int? Booking_Complete_By { get; set; }

        public DateTime? Booking_Complete_Date { get; set; }

        public int? Booking_Wizard_LastStep_id { get; set; }

        public int? Book_And_Release_Wizard_LastStep_id { get; set; }

        public int? inmate_id_sealed { get; set; }

        public DateTime? arrest_sentence_UseStart_date { get; set; }

        public int? arrest_sentence_code { get; set; }

        public int? Booking_Supervisor_Complete_Flag { get; set; }

        public int? Booking_Supervisor_Complete_BY { get; set; }

        public DateTime? Booking_Supervisor_Complete_Date { get; set; }

        public int? Booking_Supervisor_Wizard_LastStep_Id { get; set; }

        public int? arrest_sentence_AltSent_NotAllowed { get; set; }

        public int? arrest_sentence_no_early_release { get; set; }

        public int? arrest_sentence_no_day_for_day { get; set; }

        public int? arrest_sentence_no_local_parole { get; set; }

        public int? arrest_sentence_day_for_day_days { get; set; }

        public int? create_by { get; set; }

        public int? update_by { get; set; }

        public int? Originating_Agency_Id { get; set; }

        public int? arrest_sentence_day_for_day_allowed { get; set; }

        public int? arrest_sentence_method_id { get; set; }

        public int? arrest_sentence_gt_days_override { get; set; }

        public int? arrest_sentence_wt_days_override { get; set; }

        public int? arrest_sentence_day_for_day_allowed_override { get; set; }

        public int? arrest_sentence_day_for_day_days_override { get; set; }

        public DateTime? Arrest_booking_status_change { get; set; }

        public int? Arrest_booking_status_by { get; set; }

        [Column(TypeName = "date")]
        public DateTime? Arrest_Conviction_Date { get; set; }

        [StringLength(1500)]
        public string Arrest_Conviction_Note { get; set; }

        [Column(TypeName = "money")]
        public decimal? arrest_sentence_fine_paid { get; set; }

        [Column(TypeName = "money")]
        public decimal? arrest_sentence_fine_to_serve { get; set; }

        [StringLength(150)]
        public string arrest_sentence_fine_type { get; set; }

        public int? arrest_sentence_Indefinite_Hold { get; set; }
    }
}
