//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated from a template.
//
//     Manual changes to this file may cause unexpected behavior in your application.
//     Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace CaroOnline.Models
{
    using System;
    using System.Collections.Generic;
    
    public partial class Games
    {
        public int ID { get; set; }
        public Nullable<int> UserId1 { get; set; }
        public Nullable<int> UserId2 { get; set; }
        public Nullable<System.DateTime> DateGame { get; set; }
        public Nullable<int> Winer { get; set; }
    }
}
