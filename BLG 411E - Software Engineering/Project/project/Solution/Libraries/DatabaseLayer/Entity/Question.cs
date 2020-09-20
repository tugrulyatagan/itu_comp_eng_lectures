using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public partial class Question
    {
        public void Delete()
        {
            IsDeleted = true;
        }
    }

    public partial class Entities
    {
        public Question AddQuestion(Guid userID, string title, string text)
        {
            Question question = new Question()
            {
                ID = Guid.NewGuid(),
                UserID = userID,
                Title = title,
                Text = text,
                CreateDate = DateTime.Now,
                IsDeleted = false
            };
            Question.Add(question);
            return question;
        }

        public Question GetQuestionByID(Guid id)
        {
            var q = from o in Question
                    where o.ID == id && o.IsDeleted == false
                    select o;
            return q.FirstOrDefault();
        }

        public List<Question> GetQuestionList()
        {
            var q = from o in Question
                    where o.IsDeleted == false
                    orderby o.CreateDate descending
                    select o;
            return q.ToList();
        }

        public List<Question> GetQuestionListByUserID(Guid userID)
        {
            var q = from o in Question
                    where o.UserID == userID && o.IsDeleted == false
                    orderby o.CreateDate descending
                    select o;
            return q.ToList();
        }
    }
}
