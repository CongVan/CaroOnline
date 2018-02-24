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
        public void Hello()
        {
            Clients.All.hello();
        }

        public override Task OnConnected()
        {
            string User1 = Context.QueryString["UserName1"];
            string User2 = Context.QueryString["UserName2"];
            string cnnIDUser1 = Context.QueryString["cnnIDUser1"];
            string cnnIDUser2 = Context.QueryString["cnnIDUser2"];
            
            //string Turn= Context.QueryString["Turn"];
            //string Chess = Context.QueryString["Chess"];
            var g = new Dictionary<string, string>();
            g.Add("User1", User1);
            g.Add("User2", User2);
            g.Add("cnnIDUser1", cnnIDUser1);
            g.Add("cnnIDUser2", cnnIDUser2);
            g.Add("Chess", "");
            ListGame.Add(g);
            return base.OnConnected();
        }
        public override Task OnDisconnected(bool stopCalled)
        {
            return base.OnDisconnected(stopCalled);
        }
    }
}