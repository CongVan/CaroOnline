using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Web;
using Microsoft.AspNet.SignalR;

namespace CaroOnline.Hubs
{
    public class GameHub : Hub
    {
        public static List<Dictionary<string, string>> ListGame = new List<Dictionary<string, string>>();
        public static List<Dictionary<string, string>> ListUsers = new List<Dictionary<string, string>>();
        public void Hello()
        {
            Clients.All.hello("123");
        }
        public void PaintChess(string competitorId,string i,string j,string currOwner)
        {
            Clients.Client(competitorId).paintChess(competitorId, i, j, currOwner);
        }
        public void ReadyGame(string uname)
        {
            var cid = "";
            foreach (var item in ListUsers)
            {
                if(item["Name"].ToString()==uname )
                {
                    cid = item["cID"].ToString();
                    break;
                }
                
            }
            Clients.Client(cid).readygame();
        }
        public void StartGame(string uname)
        {
            var cid = "";
            foreach (var item in ListGame)
            {
                if (item["User1"].ToString() == uname)
                {
                    cid = item["Id1"].ToString();
                }
                if (item["User2"].ToString() == uname)
                {
                    cid = item["Id2"].ToString();
                }
            }
            Clients.Client(cid).startgame();
        }
        public void UpdateCnnID(string UserName)
        {
            foreach (var item in ListGame)
            {
                if(item["User1"].ToString()==UserName )
                {
                    item.Add("Id1", Context.ConnectionId);
                }
                if (item["User2"].ToString() == UserName)
                {
                    item.Add("Id2", Context.ConnectionId);
                }
            }
        }

        public override Task OnConnected()
        {
            string User1 = Context.QueryString["UserName1"];
            string User2 = Context.QueryString["UserName2"];
            string curUName = Context.QueryString["curUName"];
            //Add user list
            var u = new Dictionary<string, string>();
            u.Add("Name", curUName);
            u.Add("cID", Context.ConnectionId);
            int fl = 0;
            foreach (var item in ListUsers)
            {
                if (item["Name"].ToString() == curUName)
                {
                    fl = 1;
                    item["cID"] = Context.ConnectionId;
                }
            }
            if (fl == 0)
            {
                ListUsers.Add(u);
            }


            //string cnnIDUser1 = Context.QueryString["cnnIDUser1"];
            //string cnnIDUser2 = Context.QueryString["cnnIDUser2"];

            //string Turn= Context.QueryString["Turn"];
            //string Chess = Context.QueryString["Chess"];
            fl = 0;
            foreach (var item in ListGame)
            {
                if (item["User1"].ToString() == curUName || item["User2"] == curUName)
                {
                    fl = 1;
                }
                
            }
            if (fl == 0)
            {
                var g = new Dictionary<string, string>();
                g.Add("User1", User1);
                g.Add("User2", User2);
                //g.Add("cnnIDUser1", cnnIDUser1);
                //g.Add("cnnIDUser2", cnnIDUser2);
                g.Add("Chess", "");
                ListGame.Add(g);
            }
            
            return base.OnConnected();
        }
        public void UserLogout(string ulogout)
        {
            
        }
        public override Task OnDisconnected(bool stopCalled)
        {


            return base.OnDisconnected(stopCalled);
        }
    }
}