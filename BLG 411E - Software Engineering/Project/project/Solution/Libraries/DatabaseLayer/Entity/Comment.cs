using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public partial class Comment
    {
        public void Delete()
        {
            IsDeleted = true;
        }
    }

    public partial class Entities
    {
        private Comment AddComment(CommentType commentType, Guid? questionID, Guid? answerID, Guid userID, string text)
        {
            Comment comment = new Comment()
            {
                ID = Guid.NewGuid(),
                CommentTypeID = (int)commentType,
                QuestionID = questionID,
                AnswerID = answerID,
                UserID = userID,
                Text = text,
                CreateDate = DateTime.Now,
                IsDeleted = false
            };
            Comment.Add(comment);
            return comment;
        }

        public Comment AddQuestionComment(Guid questionID, string text, Guid userID)
        {
            return AddComment(CommentType.QuestionComment, questionID, null, userID, text);
        }

        public Comment AddAnswerComment(Guid answerID, string text, Guid userID)
        {
            return AddComment(CommentType.AnswerComment, null, answerID, userID, text);
        }

        public List<Comment> GetQuestionCommentListByQuestionID(Guid questionID)
        {
            var q = from o in Comment
                    where o.CommentTypeID == (int)CommentType.QuestionComment &&
                    o.QuestionID == questionID && o.IsDeleted == false
                    select o;
            return q.ToList();
        }

        public List<Comment> GetQuestionCommentListByUserID(Guid userID)
        {
            var q = from o in Comment
                    where o.CommentTypeID == (int)CommentType.QuestionComment &&
                    o.UserID == userID && o.IsDeleted == false
                    select o;
            return q.ToList();
        }
    }
}
