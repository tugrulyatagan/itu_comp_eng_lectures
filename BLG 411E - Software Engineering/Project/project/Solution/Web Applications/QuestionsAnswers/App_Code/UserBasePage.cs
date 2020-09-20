using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public class UserBasePage : BasePage
{
	public UserBasePage()
	{
	}

    public override void BasePage_PreInit(object sender, EventArgs e)
    {
        if (CurrentUser == null)
        {
            Response.Redirect(new SiteMapLink("QA").Url);
        }
    }
}