using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Admin_Tag_Delete : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        CurrentTag.Delete();

        Provider.SaveChanges();
        Response.Redirect(new SiteMapLink("QA.Admin.Tag").Url);
    }
}