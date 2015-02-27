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

    [Table("Facility")]
    public partial class Facility
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int Facility_id { get; set; }

        public int? Agency_id { get; set; }

        [StringLength(8)]
        public string Facility_Abbr { get; set; }

        [StringLength(100)]
        public string Facility_Name { get; set; }

        public int? Intake_Complete_NextStep { get; set; }

        public int? Booking_Complete_NextStep { get; set; }

        public int? Classify_Complete_NextStep { get; set; }

        public int? Alt_Sent_Flag { get; set; }

        public int? Delete_Flag { get; set; }

        public DateTime? Delete_Date { get; set; }

        public int? Deleted_By { get; set; }

        public int? stats_counthousing { get; set; }
    }
}
