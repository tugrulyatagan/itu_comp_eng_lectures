using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Admin_Tag_Edit : AdminBasePage
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
        tbName.Text = CurrentTag.Name;
        tbInformationText.Text = CurrentTag.InformationText;
    }

    protected void lbtSubmit_Click(object sender, EventArgs e)
    {
        CurrentTag.Name = tbName.Text.Trim();
        CurrentTag.InformationText = tbInformationText.Text.Trim();

        Provider.SaveChanges();
        Response.Redirect(new SiteMapLink("QA.Admin.Tag").Url);
    }
}