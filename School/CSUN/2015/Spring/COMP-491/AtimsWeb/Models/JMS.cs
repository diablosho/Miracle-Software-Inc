namespace AtimsWeb.Models
{
    using System;
    using System.Data.Entity;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Linq;

    /* NOTE: THIS CLASS INCLUDES AUTO GENERATED CODE !!!!
     *   Anytime a model is created using scaffolding and/or based on a table
     *   already in the database, the result may leave unnecessary code here.
     *   Please avoid using scaffolding if you can; it's better to code models
     *   and controllers by hand to ensure they are correct.
     *   
     *   Please triple check this class any time you auto-generate either a
     *   model or a controller to ensure that this is using the proper tags,
     *   relationships, and function calls.
     */

    public partial class JMS : DbContext
    {
        public JMS()
            : base("name=JMS")
        {
        }

        public virtual DbSet<AppAO_Module> AppAO_Module { get; set; }
        public virtual DbSet<AppAO_SubModule> AppAO_SubModule { get; set; }
        public virtual DbSet<Arrest> Arrests { get; set; }
        public virtual DbSet<Facility> Facilities { get; set; }
        public virtual DbSet<Housing_Unit> Housing_Unit { get; set; }
        public virtual DbSet<Incarceration> Incarcerations { get; set; }
        public virtual DbSet<Inmate> Inmates { get; set; }
        public virtual DbSet<Person> People { get; set; }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {

        }
    }
}
