using CodeLibrary.Navigation;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Admin_Badge_Default : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
        {
            BindToPage();
        }
    }

    protected void BindToPage()
    {
        rpBadge.DataSource = Provider.GetBadgeList();
        rpBadge.DataBind();

        NavigationHeader header = new NavigationHeader(Setting.NavigationHeader.DefaultHeader);
        header.AddLink(new SiteMapLink("QA.Admin.Badge.Add"));
        Navigation.AddHeader(header);
    }
}