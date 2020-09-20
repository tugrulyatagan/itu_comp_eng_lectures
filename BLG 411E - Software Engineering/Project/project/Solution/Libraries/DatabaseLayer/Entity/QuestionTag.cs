using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public partial class QuestionTag
    {
        public void Delete()
        {
            IsDeleted = true;
        }
    }

    public partial class Entities
    {
        public QuestionTag AddQuestionTag(Guid questionID, int tagID)
        {
            QuestionTag questionTag = new QuestionTag()
            {
                ID = Guid.NewGuid(),
                QuestionID = questionID,
                TagID = tagID,
                IsDeleted = false
            };
            QuestionTag.Add(questionTag);
            return questionTag;
        }

        public List<QuestionTag> GetQuestionTagListByQuestionID(Guid questionID)
        {
            var q = from o in QuestionTag
                    where o.QuestionID == questionID && o.IsDeleted == false
                    select o;
            return q.ToList();
        }
    }
}
