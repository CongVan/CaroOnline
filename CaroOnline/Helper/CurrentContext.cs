using CaroOnline.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

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
            var cur= (Users)HttpContext.Current.Session["User"];
            using (var ctx=new CaroOnlineDBEntities())
            {
                var user = ctx.Users.Where(c => c.Name == cur.Name).FirstOrDefault();
                return user;
            }
        }
        public static bool IsCurrentUrl(string controllerName, string actionName, ViewContext viewContext)
        {
            bool result = false;
            string normalizedControllerName = controllerName.EndsWith("Controller") ? controllerName : String.Format("{0}Controller", controllerName);

            if (viewContext == null) return false;
            if (String.IsNullOrEmpty(actionName)) return false;

            if (viewContext.Controller.GetType().Name.Equals(normalizedControllerName, StringComparison.InvariantCultureIgnoreCase) &&
                viewContext.Controller.ValueProvider.GetValue("action").AttemptedValue.Equals(actionName, StringComparison.InvariantCultureIgnoreCase))
            {
                result = true;
            }

            return result;
        }
    }
}