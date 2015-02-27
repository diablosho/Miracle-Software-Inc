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

    [Table("Incarceration")]
    public partial class Incarceration
    {
        [Key]
        [Column(Order = 0)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int Incarceration_id { get; set; }

        [Key]
        [Column(Order = 1)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int Inmate_id { get; set; }

        [Key]
        [Column(Order = 2)]
        [StringLength(50)]
        public string Used_Person_Last { get; set; }

        [Key]
        [Column(Order = 3)]
        [StringLength(50)]
        public string Used_Person_Frist { get; set; }

        [StringLength(50)]
        public string Used_Person_Middle { get; set; }

        [StringLength(50)]
        public string Used_Person_Suffix { get; set; }

        [StringLength(50)]
        public string Used_DOB { get; set; }

        [StringLength(50)]
        public string Used_DL { get; set; }

        [StringLength(50)]
        public string Used_DL_State { get; set; }

        [StringLength(50)]
        public string Used_Phone_Number { get; set; }

        [StringLength(50)]
        public string Used_SSN { get; set; }

        [StringLength(50)]
        public string Used_FBI { get; set; }

        [StringLength(50)]
        public string Used_CII { get; set; }

        [StringLength(50)]
        public string Used_Alien { get; set; }

        [Key]
        [Column(Order = 4)]
        public DateTime Date_In { get; set; }

        public DateTime? Release_Out { get; set; }

        public int? Reactivate_Flag { get; set; }

        public int? Incarceration_Days { get; set; }

        public int? aka_id { get; set; }

        public int? current_good { get; set; }

        public int? current_work { get; set; }

        public int? original_good { get; set; }

        public int? sent_days_minus_PC { get; set; }

        public int? tot_sent_days { get; set; }

        public int? tot_pre_cr_days { get; set; }

        public int? tot_present_credits_other { get; set; }

        public int? tot_days_stayed { get; set; }

        public int? sent_forthwith_flag { get; set; }

        public int? early_release_40186 { get; set; }

        public int? early_release_40241 { get; set; }

        public int? overall_sent_gt_days { get; set; }

        public int? overall_sent_wt_days { get; set; }

        public DateTime? overall_final_release_date { get; set; }

        public DateTime? overall_sent_exp_date { get; set; }

        public DateTime? parole_elig_date { get; set; }

        public int? days_to_serve { get; set; }

        public int? actual_days_to_serve { get; set; }

        public int? In_officer_id { get; set; }

        public int? Out_officer_id { get; set; }

        [StringLength(1500)]
        public string Overall_Condition_of_Release { get; set; }

        [StringLength(150)]
        public string Overall_Release_Information { get; set; }

        public int? Transport_Flag { get; set; }

        public int? Release_To_Other_Agency_ID { get; set; }

        [StringLength(100)]
        public string Release_To_Other_Agency_Name { get; set; }

        public int? Transport_CoOp_Flag { get; set; }

        public int? Transport_CoOp_Route { get; set; }

        public int? Transport_Hold_Flag { get; set; }

        public int? Transport_Hold_Type { get; set; }

        [StringLength(100)]
        public string Transport_Hold_name { get; set; }

        public DateTime? Transport_Schedule_Date { get; set; }

        [StringLength(250)]
        public string Transport_Instructions { get; set; }

        [StringLength(150)]
        public string Transport_inmate_cautions { get; set; }

        [StringLength(50)]
        public string Transport_inmate_bail { get; set; }

        public int? Transport_inmate_Return { get; set; }

        public int? Intake_Complete_Flag { get; set; }

        public int? Intake_Complete_By { get; set; }

        public DateTime? Intake_Complete_Date { get; set; }

        [Key]
        [Column(Order = 5)]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int Facility_id_In { get; set; }

        public int? Facility_id_Out { get; set; }

        public int? Book_And_Release_Flag { get; set; }

        public int? Intake_Wizard_LastStep_id { get; set; }

        public int? Booking_Wizard_LastStep_id { get; set; }

        public int? Release_Wizard_LastStep_id { get; set; }

        public int? Book_And_Release_Wizard_LastStep_id { get; set; }

        public int? Release_Clear_Flag { get; set; }

        public int? Release_Clear_By { get; set; }

        public DateTime? Release_Clear_Date { get; set; }

        public DateTime? overall_sent_start_date { get; set; }

        public int? Book_BookData_Flag { get; set; }

        public int? Book_BookData_By { get; set; }

        public DateTime? Book_BookData_Date { get; set; }

        public int? Book_Complete_Flag { get; set; }

        public int? Book_Complete_By { get; set; }

        public DateTime? Book_Complete_Date { get; set; }

        [Column(TypeName = "money")]
        public decimal? bail_amount_Total { get; set; }

        public int? bail_no_bail_flag_Total { get; set; }

        [StringLength(1)]
        public string Charge_Level { get; set; }

        public int? Charge_Level_Override_Flag { get; set; }

        public int? Release_Complete_Flag { get; set; }

        public int? Release_Complete_By { get; set; }

        public DateTime? Release_Complete_Date { get; set; }

        public int? Fast_Book_Flag { get; set; }

        public int? inmate_id_sealed { get; set; }

        public int? Booking_Supervisor_Complete_Flag { get; set; }

        public int? Booking_Supervisor_Complete_BY { get; set; }

        public DateTime? Booking_Supervisor_Complete_Date { get; set; }

        public int? Booking_Supervisor_Wizard_LastStep_Id { get; set; }

        public int? Release_Supervisor_Complete_Flag { get; set; }

        public int? Release_Supervisor_Complete_BY { get; set; }

        public DateTime? Release_Supervisor_Complete_Date { get; set; }

        public int? Release_Supervisor_Wizard_LastStep_Id { get; set; }

        public int? Current_AltSent_id { get; set; }

        public int? overall_sent_Manual { get; set; }

        public DateTime? overall_sent_Manual_date { get; set; }

        public int? overall_sent_Manual_by { get; set; }

        public DateTime? Transport_UpdateDate { get; set; }

        public int? Transport_UpdateBy { get; set; }
    }
}
