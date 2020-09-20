using Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

public class AdminBasePage : BasePage
{
	public AdminBasePage()
	{
	}

    public override void BasePage_PreInit(object sender, EventArgs e)
    {
        if (CurrentUser == null ||CurrentUser.UserTypeID != (int)UserType.Admin)
        {
            Response.Redirect(new SiteMapLink("QA").Url);
        }
    }
}