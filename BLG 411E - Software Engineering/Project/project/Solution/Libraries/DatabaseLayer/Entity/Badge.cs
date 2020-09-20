using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public partial class Badge
    {
        public void Delete()
        {
            IsDeleted = true;
        }
    }

    public partial class Entities
    {
        public Badge AddBadge(string name, string informationText, string imagePath)
        {
            Badge badge = new Badge()
            {
                Name = name,
                InformationText = informationText,
                ImagePath = imagePath,
                IsDeleted = false
            };
            Badge.Add(badge);
            return badge;
        }

        public Badge GetBadgeByID(int id)
        {
            var q = from o in Badge
                    where o.ID == id && o.IsDeleted == false
                    select o;
            return q.FirstOrDefault();
        }

        public List<Badge> GetBadgeList()
        {
            var q = from o in Badge
                    where o.IsDeleted == false
                    select o;
            return q.ToList();
        }
    }
}
