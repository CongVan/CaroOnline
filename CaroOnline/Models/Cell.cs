using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CaroOnline.Models
{
    public class Cell
    {
        public const int Width = 30;
        public const int Height = 30;
        public int Row { get; set; }
        public int Column { get; set; }

        public int PX { get; set; }
        public int PY { get; set; }

        public int Owner { get; set; }
        public Cell(int Row , int Column, int PX ,int PY, int Owner)
        {
            this.Row = Row;
            this.Column = Column;
            this.PX = PX;
            this.PY = PY;
            this.Owner = Owner;
        }
    }
}