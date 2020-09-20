using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Admin_Badge_Edit : AdminBasePage
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
        tbName.Text = CurrentBadge.Name;
        tbInformationText.Text = CurrentBadge.InformationText;
        tbImagePath.Text = CurrentBadge.ImagePath;
    }

    protected void lbtSubmit_Click(object sender, EventArgs e)
    {
        CurrentBadge.Name = tbName.Text.Trim();
        CurrentBadge.InformationText = tbInformationText.Text.Trim();
        CurrentBadge.ImagePath = tbImagePath.Text.Trim();

        Provider.SaveChanges();
        Response.Redirect(new SiteMapLink("QA.Admin.Badge").Url);
    }
}