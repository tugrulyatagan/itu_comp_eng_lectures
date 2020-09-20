using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public partial class Reputation
    {
        public void Delete()
        {
            IsDeleted = true;
        }
    }

    public partial class Entities
    {
        public Reputation AddReputation(string name, string informationText, int value)
        {
            Reputation reputation = new Reputation()
            {
                Name = name,
                InformationText = informationText,
                Value = value,
                IsDeleted = false
            };
            Reputation.Add(reputation);
            return reputation;
        }
    }
}
