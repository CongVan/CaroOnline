using CaroOnline.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace CaroOnline.Controllers
{
    public class HomeController : Controller
    {
        // GET: Home
        public ActionResult Index()
        {
            ViewBag.msgError = TempData["msgError"] != null ? TempData["msgError"].ToString() : null;
            ViewBag.msgSuccess = TempData["msgSuccess"] != null ? TempData["msgSuccess"].ToString() : null;
            return View();
        }
        public ActionResult Login()
        {
            ViewBag.msgError = TempData["msgError"]!=null?TempData["msgError"].ToString():null;
            ViewBag.msgSuccess = TempData["msgSuccess"] != null ? TempData["msgSuccess"].ToString() : null;
            return View();
        }
        [HttpPost]
        public ActionResult Login(Users model)
        {
            
            using (var ctx= new CaroOnlineDBEntities())
            {
                var u = ctx.Users.Where(c => c.Name == model.Name && c.Pass == model.Pass).FirstOrDefault();
                if (u != null)
                {
                    TempData["msgSuccess"] = "Đăng nhập thành công!";
                    return Redirect("/Home/Index");
                }
                TempData["msgError"] = "Tên đăng nhập hoặc mật khẩu không đúng!";
                
                return Redirect("/Home/Login"); 
            }
            return View();
        }
        [HttpPost]
        public ActionResult Register(Users model)
        {
            
            using(var ctx= new CaroOnlineDBEntities())
            {
                try
                {
                    ctx.Users.Add(model);
                    ctx.SaveChanges();
                }
                catch (Exception ex)
                {
                    TempData["msgError"] = "Lỗi đăng ký : " +ex.Message;
                    return Redirect("/Home/Login");
                }
                TempData["msgSuccess"] = "Đăng ký thành công";
                return Redirect("/Home/Login");
            }
        }
    }
}