using CaroOnline.Helper;
using CaroOnline.Hubs;
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
           // string t= String.Format("{0:N0}", 9001561346);
            if (CurrentContext.IsLogged() == false)
            {
                return Redirect("/Home/Login");
            }   

            ViewBag.msgError = TempData["msgError"] != null ? TempData["msgError"].ToString() : null;
            ViewBag.msgSuccess = TempData["msgSuccess"] != null ? TempData["msgSuccess"].ToString() : null;
            //string currName = CurrentContext.GetCurUser().Name;
            //var Users = new List<Users>();
            //var lst = OnlineHub.ListUsers;
            //try
            //{
            //    using (var ctx = new CaroOnlineDBEntities())
            //    {
            //        foreach (var item in lst)
            //        {
            //            string sName = item["Name"].ToString();
            //            if (sName != currName)
            //            {

            //                var us = ctx.Users.Where(c => c.Name == sName).FirstOrDefault();
            //                if (us != null)
            //                {
            //                    Users.Add(us);
            //                }
            //            }

            //        }
            //        return View(Users);
            //    }
            //}
            //catch (Exception ex)
            //{

            //    return View(Users);
            //}
            return View();
            
            

        }
        public ActionResult ReloadUser()
        {
            string currName = CurrentContext.GetCurUser().Name;
            var Users = new List<Object>();
            var lst = OnlineHub.ListUsers;
            try
            {
                using (var ctx = new CaroOnlineDBEntities())
                {
                    foreach (var item in lst)
                    {
                        string sName = item["Name"].ToString();
                        if (sName != currName)
                        {
                            var tempID = item["cID"].ToString();
                            var us = ctx.Users.Where(c => c.Name == sName).Select(c => new { ID = c.ID, Name = c.Name, CID = tempID }).FirstOrDefault();
                            if (us != null)
                            {
                                Users.Add(us);
                            }
                        }

                    }
                    return Json(Users, JsonRequestBehavior.AllowGet);
                }
            }
            catch (Exception )
            {

                return Json("", JsonRequestBehavior.AllowGet);
            }
            

        }
        public ActionResult Login()
        {
            if (CurrentContext.IsLogged())
            {
                return Redirect("/Home/Index");
            }


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
                    Response.Cookies["userID"].Value = u.ID.ToString();
                    Response.Cookies["userID"].Expires = DateTime.Now.AddDays(7);

                    Session["isLogin"] = 1;
                    Session["User"] = u;

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

        
        public ActionResult Logout()
        {
            CurrentContext.Detroy();
            
            return RedirectToAction("Login", "Home");
        }
        public ActionResult Play()
        {
            if (CurrentContext.IsLogged() == false)
            {
                return Redirect("/Home/Login");
            }
            var CB = new Cell[21, 21];
            for (int i = 0; i < 21; i++)
            {
                for (int j = 0; j < 21; j++)
                {
                    CB[i, j] = new Cell(i, j, j * 30, i * 30, 0);
                }
            }

            return View(CB);
        }
     
    }
}