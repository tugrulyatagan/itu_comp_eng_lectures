using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public partial class UserTag
    {
        public void Delete()
        {
            IsDeleted = true;
        }
    }

    public partial class Entities
    {
        public UserTag AddUserTag(UserTagType userTagType, int tagID, Guid userID)
        {
            UserTag userTag = new UserTag()
            {
                ID = Guid.NewGuid(),
                UserTagTypeID = (int)userTagType,
                TagID = tagID,
                UserID = userID,
                IsDeleted = false
            };
            UserTag.Add(userTag);
            return userTag;
        }

        public UserTag GetUserTagByID(Guid id)
        {
            var q = from o in UserTag
                    where o.ID == id && o.IsDeleted == false
                    select o;
            return q.FirstOrDefault();
        }

        public List<UserTag> GetUserTagListByUserTagTypeAndUserID(UserTagType userTagType, Guid userID)
        {
            var q = from o in UserTag
                    where o.UserTagTypeID == (int)userTagType && o.UserID == userID && o.IsDeleted == false
                    select o;
            return q.ToList();
        }
    }
}
