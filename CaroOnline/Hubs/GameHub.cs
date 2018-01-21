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
            string User1= Context.QueryString["User1"];
            string User2 = Context.QueryString["User2"];
            //string Turn= Context.QueryString["Turn"];
            //string Chess = Context.QueryString["Chess"];
            var g = new Dictionary<string, string>();
            g.Add("User1", User1);
            g.Add("User2", User2);
            return base.OnConnected();
        }
    }
}