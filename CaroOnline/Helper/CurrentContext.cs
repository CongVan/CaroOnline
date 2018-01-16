using CaroOnline.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CaroOnline.Helper
{
    public class CurrentContext
    {
        public static bool IsLogged()
        {
            var flag = HttpContext.Current.Session["isLogin"];
            if (flag == null || (int)flag == 0)
            {
                if (HttpContext.Current.Request.Cookies["userID"] != null)
                {

                    int id = Convert.ToInt32(HttpContext.Current.Request.Cookies["userID"].Value);
                    using (var ctx = new CaroOnlineDBEntities())
                    {
                        var user = ctx.Users.Where(u => u.ID == id).FirstOrDefault();
                        if (user == null)
                        {
                            return false;
                        }
                        HttpContext.Current.Session["isLogin"] = 1;
                        HttpContext.Current.Session["User"] = user;

                    }
                    return true;

                }

                return false;


            }
            return true;
        }
        public static void Detroy()
        {
            HttpContext.Current.Session["isLogin"] = 0;
            HttpContext.Current.Session["User"] = null;
            //HttpCookie login = new HttpCookie("userID");
            //login.Expires = DateTime.Now.AddDays(-7d);


            HttpContext.Current.Response.Cookies["userID"].Expires = DateTime.Now.AddDays(-8);


        }
        public static Users GetCurUser()
        {
            return (Users)HttpContext.Current.Session["User"];
        }
    }
}