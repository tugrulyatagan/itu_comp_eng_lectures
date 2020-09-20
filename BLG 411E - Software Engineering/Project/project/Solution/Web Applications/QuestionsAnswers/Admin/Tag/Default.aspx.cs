using CodeLibrary.Navigation;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Admin_Tag_Default : AdminBasePage
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
        rpTag.DataSource = Provider.GetTagList();
        rpTag.DataBind();

        NavigationHeader header = new NavigationHeader(Setting.NavigationHeader.DefaultHeader);
        header.AddLink(new SiteMapLink("QA.Admin.Tag.Add"));
        Navigation.AddHeader(header);
    }
}