using CaroOnline.Helper;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace CaroOnline.Filter
{
    public class CheckLoginAttribute : ActionFilterAttribute
    {
        
        public override void OnActionExecuting(ActionExecutingContext filterContext)
        {
            if (CurrentContext.IsLogged() == false)
            {
                filterContext.Result = new RedirectResult("/Home/Login");
                return;
            }
            
            base.OnActionExecuting(filterContext);
        }
    }
}