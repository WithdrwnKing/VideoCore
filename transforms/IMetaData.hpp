/*
 
 Video Core
 Copyright (C) 2014 James G. Hurley
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 USA
 
*/

#ifndef videocore_IMetadata_hpp
#define videocore_IMetadata_hpp

#include <map>
#include <tuple>
#include <string>
#include <boost/lexical_cast.hpp>

namespace videocore
{
    struct IMetadata
    {
        IMetadata(double ts) : timestampDelta(ts) {};
        virtual ~IMetadata() {};
        
        virtual const int32_t type() const = 0;
        
        double timestampDelta;
    };
    
    template <int32_t MetaDataType, typename... Types>
    struct MetaData : public IMetadata
    {
        MetaData<Types...>(double ts) : IMetadata(ts) {};
        
        virtual const int32_t type() const { return MetaDataType; };
        
        void setData(Types... data)
        {
            m_data = std::make_tuple(data...);
        };
        template<std::size_t idx>
        void setValue(typename std::tuple_element<idx, std::tuple<Types...> >::type value)
        {
            auto & v = getData<idx>();
            v = value;
        }
        template<std::size_t idx>
        typename std::tuple_element<idx, std::tuple<Types...> >::type & getData() const {
            return const_cast<typename std::tuple_element<idx, std::tuple<Types...> >::type &>(std::get<idx>(m_data));
        }
        size_t size() const
        {
            return std::tuple_size<std::tuple<Types...> >::value;
        }
    private:
        std::tuple<Types...> m_data;
    };
    
}

#endif
