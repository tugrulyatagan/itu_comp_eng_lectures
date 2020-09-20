using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Model;

public partial class Admin_Badge_Add : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
    }

    protected void lbtSubmit_Click(object sender, EventArgs e)
    {
        Badge badge = Provider.AddBadge(tbName.Text.Trim(), tbInformationText.Text.Trim(), tbImagePath.Text.Trim());

        Provider.SaveChanges();
        Response.Redirect(new SiteMapLink("QA.Admin.Badge").Url);
    }
}