using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public partial class Answer
    {
        public void Delete()
        {
            IsDeleted = true;
        }
    }

    public partial class Entities
    {
        public Answer AddAnswer(Guid userID, Guid questionID, string text)
        {
            Answer answer = new Answer()
            {
                ID = Guid.NewGuid(),
                UserID = userID,
                QuestionID = questionID,
                Text = text,
                CreateDate = DateTime.Now,
                IsDeleted = false
            };
            Answer.Add(answer);
            return answer;
        }

        public Answer GetAnswerByID(Guid id)
        {
            var q = from o in Answer
                    where o.ID == id && o.IsDeleted == false
                    select o;
            return q.FirstOrDefault();
        }

        public List<Answer> GetAnswerListByQuestionID(Guid questionID)
        {
            var q = from o in Answer
                    where o.QuestionID == questionID && o.IsDeleted == false
                    select o;
            return q.ToList();
        }

        public List<Answer> GetAnswerListByUserID(Guid userID)
        {
            var q = from o in Answer
                    where o.UserID == userID && o.IsDeleted == false
                    select o;
            return q.ToList();
        }
    }
}
