using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CodeLibrary.Navigation
{
    public class Navigation
    {
        private List<NavigationHeader> HeaderList;

        public Navigation()
        {
            HeaderList = new List<NavigationHeader>();
        }

        public Navigation AddHeader(NavigationHeader header)
        {
            HeaderList.Add(header);
            return this;
        }

        public bool IsEmpty()
        {
            return HeaderList.Count == 0;
        }

        public string Print()
        {
            string output = "<ul class=\"" + NavigationSetting.NavigationCssClass + "\">";
            foreach (NavigationHeader header in HeaderList)
            {
                output += "\n" + "<li class=\"" + NavigationSetting.NavigationHeaderCssClass +"\">" + header.Text + "</li>";
                foreach (Link link in header.GetLinkList())
                {
                    output += "\n" + "<li><a href=\"" + link.Url + "\">";
                    if (link.Icon != null)
                        output += "<i class=\"" + link.Icon + "\"></i>";
                    output += link.Text + "</a></li>";
                }
            }
            output += "</ul>";
            return output;
        }
    }
}