using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Admin_Badge_Delete : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        CurrentBadge.Delete();

        Provider.SaveChanges();
        Response.Redirect(new SiteMapLink("QA.Admin.Badge").Url);
    }
}