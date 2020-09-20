using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public partial class UserBadge
    {
        public void Delete()
        {
            IsDeleted = true;
        }
    }

    public partial class Entities
    {
        public UserBadge AddUserBadge(Guid userID, int badgeID)
        {
            UserBadge userBadge = new UserBadge()
            {
                ID = Guid.NewGuid(),
                UserID = userID,
                BadgeID = badgeID,
                IsDeleted = false
            };
            UserBadge.Add(userBadge);
            return userBadge;
        }
    }
}
