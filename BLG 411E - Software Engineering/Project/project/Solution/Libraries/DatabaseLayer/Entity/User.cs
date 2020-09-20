using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public partial class User
    {
        public void Delete()
        {
            IsDeleted = true;
        }

        public void UpdatePassword(string password)
        {
            Password = password;
        }
    }

    public partial class Entities
    {
        public User AddUser(UserType userType, string name, string surname, string mail, string username, string password)
        {
            User user = new User()
            {
                ID = Guid.NewGuid(),
                UserTypeID = (int)userType,
                Name = name,
                Surname = surname,
                Mail = mail,
                Username = username,
                Password = password,
                Reputation = 1,
                RegisterDate = DateTime.Now,
                IsDeleted = false
            };
            User.Add(user);
            return user;
        }

        public User GetUserByID(Guid id)
        {
            var q = from o in User
                    where o.ID == id && o.IsDeleted == false
                    select o;
            return q.FirstOrDefault();
        }

        public User GetUserByUsernameAndPassword(string username, string password)
        {
            var q = from o in User
                    where o.Password == password && o.Username == username && o.IsDeleted == false
                    select o;
            return q.FirstOrDefault();
        }

        public List<User> GetUserList()
        {
            var q = from o in User
                    where o.IsDeleted == false
                    select o;
            return q.ToList();
        }
    }
}
