using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public partial class Tag
    {
        public void Delete()
        {
            IsDeleted = true;
        }
    }

    public partial class Entities
    {
        public Tag AddTag(string name, string informationText)
        {
            Tag tag = new Tag()
            {
                Name = name,
                InformationText = informationText,
                IsDeleted = false
            };
            Tag.Add(tag);
            return tag;
        }

        public Tag GetTagByID(int id)
        {
            var q = from o in Tag
                    where o.ID == id && o.IsDeleted == false
                    select o;
            return q.FirstOrDefault();
        }

        public List<Tag> GetTagList()
        {
            var q = from o in Tag
                    where o.IsDeleted == false
                    select o;
            return q.ToList();
        }
    }
}
