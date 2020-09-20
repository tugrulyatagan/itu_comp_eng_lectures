using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Admin_Tag_Add : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
    }

    protected void lbtSubmit_Click(object sender, EventArgs e)
    {
        Tag tag = Provider.AddTag(tbName.Text.Trim(), tbInformationText.Text.Trim());

        Provider.SaveChanges();
        Response.Redirect(new SiteMapLink("QA.Admin.Tag").Url);
    }
}