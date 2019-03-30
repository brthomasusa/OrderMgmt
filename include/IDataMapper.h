#pragma once

#include "ocilib.hpp"
#include <memory>
#include <string>
#include "Logger.h"

using namespace std;
using namespace ocilib;
using namespace ServiceLayer;

namespace DataAccess
{
    template <typename T>
    class IDataMapper
    {

    public:
        IDataMapper() = default;
        virtual ~IDataMapper() = default;

        virtual shared_ptr<T> findById(int entityId)
        {
            Logger::instance().LogInfo("Entering IDataMapper::findById");

            shared_ptr<T> entity;

            try {

                Environment::Initialize();
                Connection connection("oracle18db/xepdb1", "cust_orders", "Info77Gum");
                Statement stmt(connection);

                stmt.Prepare(getFindStatement());
                stmt.Bind(":1", entityId, BindInfo::In);
                stmt.ExecutePrepared();

                Resultset rs = stmt.GetResultset();

                entity = load(entityId, rs);

            }
            catch (exception &ex)
            {
                Logger::instance().LogError(ex.what());
            }

            Logger::instance().LogInfo("Leaving IDataMapper::findById");
            Environment::Cleanup();
            return entity;
        }

        virtual vector<shared_ptr<T>> findChildren(int parentId)
        {
            Logger::instance().LogInfo("Entering IDataMapper::findChildren");

            vector<shared_ptr<T>> list;

            try
            {

                Environment::Initialize();
                Connection connection("oracle18db/xepdb1", "cust_orders", "Info77Gum");
                Statement stmt(connection);

                stmt.Prepare(getFindChildrenStatement());
                stmt.Bind(":1", parentId, BindInfo::In);
                stmt.ExecutePrepared();

                Resultset rs = stmt.GetResultset();

                list = loadAll(rs);
            }
            catch (exception &ex)
            {
                Logger::instance().LogError(ex.what());
            }

            Environment::Cleanup();
            Logger::instance().LogInfo("Leaving IDataMapper::findChildren");
            return list;
        }

        virtual vector<shared_ptr<T>> findAll()
        {
            Logger::instance().LogInfo("Entering IDataMapper::findAll");

            vector<shared_ptr<T>> list;

            try {

                Environment::Initialize();
                Connection connection("oracle18db/xepdb1", "cust_orders", "Info77Gum");
                Statement stmt(connection);
                stmt.Execute(getFindAllStatement());

                Resultset rs = stmt.GetResultset();

                list = loadAll(rs);

            }
            catch (exception &ex)
            {
                Logger::instance().LogError(ex.what());
            }

            Environment::Cleanup();
            Logger::instance().LogInfo("Leaving IDataMapper::findAll");
            return list;
        }

        virtual void insertEntity(T& entity) = 0;
        virtual void updateEntity(const T& entity) = 0;

        virtual void deleteEntity(int entityId)
        {
            Logger::instance().LogInfo("Entering IDataMapper::deleteEntity");

            try {

                Environment::Initialize();
                Connection connection("oracle18db/xepdb1", "cust_orders", "Info77Gum");
                Statement stmt(connection);

                stmt.Prepare(getDeleteStatement());
                stmt.Bind(":1", entityId, BindInfo::In);
                stmt.ExecutePrepared();
                connection.Commit();

            }
            catch (exception &ex)
            {
                Logger::instance().LogError(ex.what());
            }

            Environment::Cleanup();
            Logger::instance().LogInfo("Leaving IDataMapper::deleteEntity");
        }

    protected:
        virtual shared_ptr<T> load(int id, Resultset& rs) = 0;
        virtual vector<shared_ptr<T>> loadAll(Resultset& rs) = 0;

        virtual const string& getFindStatement() = 0;
        virtual const string& getFindChildrenStatement() = 0;
        virtual const string& getFindAllStatement() = 0;
        virtual const string& getDeleteStatement() = 0;

    };
}
