using CodeLibrary.Sitemap;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.UI;

public class SiteMapLink : Link
{
    SiteMapNode Node;
    private NameValueCollection QueryStrings;

    public SiteMapLink(string key)
    {
        QueryStrings = new NameValueCollection();
        Node = SiteMap.Provider.FindSiteMapNodeFromKey(key);
        Text = Node.Title;
        Url = BuildURL();
    }

    public SiteMapLink AddQueryString(string name, string value)
    {
        QueryStrings.Add(name, value);
        return this;
    }

    public override string ToString()
    {
        string url = BuildURL();

        string output = "<a href=\"" + url + "\" title=\"" + Node.Title + "\">";
        if (Icon != null)
            output += "<i class=\"" + Icon + "\"></i>";
        output += " " + Node.Title + "</a>";
        return output;
    }

    public string ToString(string text)
    {
        string url = BuildURL();

        string output = "<a href=\"" + url + "\" title=\"" + Node.Title + "\">";
        if (Icon != null)
            output += "<i class=\"" + Icon + "\"></i>";
        output += " " + text + "</a>";
        return output;
    }

    public string PrintIcon()
    {
        string url = BuildURL();

        string output = "<a href=\"" + url + "\" title=\"" + Node.Title + "\">";
        if (Icon != null)
            output += "<i class=\"" + Icon + "\"></i></a>";
        return output;
    }

    protected string BuildURL()
    {
        string url = Node.Url;
        NameValueCollection sitemapQueryStrings = (SiteMap.Provider as SmartSiteMapProvider).GetQueryString(Node, HttpContext.Current);

        foreach (string qsName in QueryStrings.AllKeys)
        {
            sitemapQueryStrings.Set(qsName, QueryStrings[qsName]);
        }

        return url + (SiteMap.Provider as SmartSiteMapProvider).NameValueCollectionToString(sitemapQueryStrings);
    }
}