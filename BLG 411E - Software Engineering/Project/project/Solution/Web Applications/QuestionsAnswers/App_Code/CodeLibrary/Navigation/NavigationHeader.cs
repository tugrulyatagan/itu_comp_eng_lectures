using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CodeLibrary.Navigation
{
    public class NavigationHeader
    {
        public string Text;
        private List<Link> LinkList;

        public NavigationHeader(string text)
        {
            Text = text;
            LinkList = new List<Link>();
        }

        public NavigationHeader AddLink(Link link)
        {
            LinkList.Add(link);
            return this;
        }

        public List<Link> GetLinkList()
        {
            return LinkList;
        }
    }
}