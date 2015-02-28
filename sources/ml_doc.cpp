/*
 * ml-lib, a machine learning library for Max and Pure Data
 * Copyright (C) 2013 Carnegie Mellon University
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ml_doc.h"

namespace ml_doc
{
    
    std::string class_descriptor::print(void)
    {
        std::string out = name + ": " + desc + "\n";
        
        for(auto &attr : message_descriptors)
        {
            out += attr->print();
            out += "\n";
        }
        return out;
    }

    
    // ml_doc_manager implementation
    ml_doc_manager& ml_doc_manager::shared_instance()
    {
        static ml_doc_manager instance;
        instance.populate();
        return instance;
    }

    std::string ml_doc_manager::descriptor_for_class(std::string class_name)
    {
        auto it = descriptors.find(class_name);
        std::unique_ptr<class_descriptor> descriptor;
        
        if (it == descriptors.end())
        {
            return "";
        }
        
        return it->second->print();
    }
    
    void ml_doc_manager::populate(void)
    {
        std::unique_ptr<class_descriptor> ml_mlp(new class_descriptor());
        ranged_message_descriptor<int> min_epochs;
        
        min_epochs.name = "min_epochs";
        min_epochs.desc = "the minimum number of training iterations";
        min_epochs.min = 0;
        min_epochs.max = 100;
        min_epochs.def = 10;
        min_epochs.allowed_values = {1, 2, 3, 4, 5};
        
        ml_mlp->add_message_descriptor(min_epochs);
        ml_mlp->name = "ml.mlp";
        ml_mlp->desc = "blah blah blah";
        
        descriptors.emplace(std::pair<std::string, std::unique_ptr<class_descriptor> >("ml.mlp", std::move(ml_mlp)));
    }

}