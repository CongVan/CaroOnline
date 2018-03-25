using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Microsoft.AspNet.SignalR;
using Microsoft.AspNet.SignalR.Hubs;
using System.Threading.Tasks;
using System.Data.Entity;
using CaroOnline.Models;
using System.Collections.Concurrent;

namespace CaroOnline.Hubs
{
    public static class UserHandler
    {
        public static HashSet<string> ConnectedIds = new HashSet<string>();
    }

    public class OnlineHub : Hub
    {
        public static List<Dictionary<string, string>> ListUsers = new List<Dictionary<string, string>>();
        //public List<Users> UserOnline { get; set; }
        public void Hello()
        {
            Clients.All.hello();
        }
        public void Send(string name, string message)
        {
            Clients.All.addNewMessageToPage(name, message);
            //Clients.Client(Context.ConnectionId).sendTo(name, message,Context.ConnectionId);
        }
        public void SendTo(string name, string message, string connectionID)
        {
            //Clients.All.addNewMessageToPage(name, message);
            Clients.Client(Context.ConnectionId).sendTo(name, message, Context.ConnectionId);
        }
        public void NotOkRestart(string name)
        {
            var cid = "";
            foreach (var item in ListUsers)
            {
                if (item["Name"].ToString() == name)
                {
                    cid = item["cID"].ToString();
                    break;
                }

            }

            Clients.Client(cid).notOkRestart();
        }
        public void CloseRestart(string name)
        {
            var cid = "";
            foreach (var item in ListUsers)
            {
                if (item["Name"].ToString() == name)
                {
                    cid = item["cID"].ToString();
                    break;
                }

            }

            Clients.Client(cid).closeRestart();
        }
        public void RestartGame(string name,string from,string link)
        {
            var cid = "";
            foreach (var item in ListUsers)
            {
                if (item["Name"].ToString() == name)
                {
                    cid = item["cID"].ToString();
                    break;
                }

            }

            Clients.Client(cid).restartGame(from,link);
            //Clients.All.addNewMessageToPage(name, message);
            //Clients.Client(Context.ConnectionId).sendTo(name, message, Context.ConnectionId);
        }
        public void OkRestart(string name, string link)
        {
            var cid = "";
            foreach (var item in ListUsers)
            {
                if (item["Name"].ToString() == name)
                {
                    cid = item["cID"].ToString();
                    break;
                }

            }
            Clients.Client(cid).okRestart(link);
            //Clients.All.addNewMessageToPage(name, message);
            //Clients.Client(Context.ConnectionId).sendTo(name, message, Context.ConnectionId);
        }
        public void updateConnectionID()
        {
            Clients.All.updateConnectionID(ListUsers);
        }
        public void ReloadUsers()
        {
            Clients.All.reloadUsers();
        }
        public void PairingGame(string uNameFrom, string userToID,string uNameTo,string userToCnnID)
        {
            string uCnnIdFrom = Context.ConnectionId;
            Clients.Client(userToCnnID).pairingGame(uNameFrom,uCnnIdFrom ,uNameTo);
        }
        public void NoPairing(string userCnnIDTo,string uNameFrom)
        {
            string uCnnIdFrom = Context.ConnectionId;
            Clients.Client(userCnnIDTo).noPairing(userCnnIDTo, uNameFrom, uCnnIdFrom);
        }
        public void YesPairing(string cnnIDFrom, string cnnIDTo)
        {
            string uCnnIdFrom = Context.ConnectionId;
            string uNameFrom="", uNameTo="";
            foreach (var item in ListUsers)
            {
                if (item["cID"].ToString() == cnnIDFrom)
                {
                    uNameFrom = item["Name"].ToString();
                }
                if (item["cID"].ToString() == cnnIDTo)
                {
                    uNameTo = item["Name"].ToString();
                }
            }
            
            Clients.Client(cnnIDTo).yesPairing(cnnIDFrom, cnnIDTo, uNameFrom, uNameTo);
        }
        public override Task OnConnected()
        {
           // string name = Context.User.Identity.Name;

            string UName=Context.QueryString["Uname"];
            var u = new Dictionary<string, string>();
            u.Add("Name", UName);
            u.Add("cID", Context.ConnectionId);
            u.Add("inGame", "false");
            int fl = 0;
            foreach (var item in ListUsers)
            {
                if (item["Name"].ToString() == UName)
                {
                    fl = 1;
                    item["cID"] = Context.ConnectionId;
                }
            }
            if (fl == 0)
            {
                ListUsers.Add(u);
            }
            ReloadUsers();
            //UserHandler.ConnectedIds.Add(Context.ConnectionId);
            return base.OnConnected();
        }

        public override Task OnDisconnected(bool stopCalled)
        {
            

          //  var u = new Dictionary<string, string>();
          //  u.Add("Name","");
           // u.Add("cID", Context.ConnectionId);

            foreach (var item in ListUsers)
            {
                if (item["cID"].ToString() == Context.ConnectionId)
                {
                    ListUsers.Remove(item);
                    break;
                }
            }
            ReloadUsers();

          //  UserHandler.ConnectedIds.Remove(Context.ConnectionId);
            return base.OnDisconnected(stopCalled);
        }
        //public override Task OnConnected()
        //{
        //    string userName = Context.User.Identity.Name;
        //    string connectionId = Context.ConnectionId;

        //    var user = Users.GetOrAdd(userName, _ => new User
        //    {
        //        Name = userName,
        //        ConnectionIds = new HashSet<string>()
        //    });

        //    lock (user.ConnectionIds)
        //    {

        //        user.ConnectionIds.Add(connectionId);

        //        // TODO: Broadcast the connected user
        //    }

        //    return base.OnConnected();
        //}
        //public override Task OnDisconnected(bool stopCalled)
        //{
        //    string userName = Context.User.Identity.Name;
        //    string connectionId = Context.ConnectionId;

        //    User user;
        //    Users.TryGetValue(userName, out user);

        //    if (user != null)
        //    {

        //        lock (user.ConnectionIds)
        //        {

        //            user.ConnectionIds.RemoveWhere(cid => cid.Equals(connectionId));

        //            if (!user.ConnectionIds.Any())
        //            {

        //                User removedUser;
        //                Users.TryRemove(userName, out removedUser);

        //                // You might want to only broadcast this info if this 
        //                // is the last connection of the user and the user actual is 
        //                // now disconnected from all connections.
        //                Clients.Others.userDisconnected(userName);
        //            }
        //        }
        //    }
        //    return base.OnDisconnected(stopCalled);
        //}
    }
}