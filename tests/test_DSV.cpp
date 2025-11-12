#include "alg.h"
#include <gtest/gtest.h>
#include "../lib_DSV/DSV.h"

TEST(DSVTest, can_create_dsv) 
{
    ASSERT_NO_THROW(DSV dsv(10));
}

TEST(DSVTest, can_find_initial_elements) 
{

    DSV dsv(5);
    for (int i = 0; i < 5; i++) 
    {
        ASSERT_NO_THROW(dsv.find(i));
    }
}

TEST(DSVTest, can_unite_elements) 
{
    DSV dsv(5);
    ASSERT_NO_THROW(dsv.unite(0, 1));
    ASSERT_NO_THROW(dsv.unite(2, 3));
}

TEST(DSVTest, can_check_connections)
{
    DSV dsv(5);
    dsv.unite(0, 1); 
    ASSERT_NO_THROW(dsv.connected(0, 1));
    ASSERT_NO_THROW(dsv.connected(0, 2));
}

TEST(DSVTest, can_copy_dsv)
{
    DSV dsv1(5);
    dsv1.unite(0, 1);
    ASSERT_NO_THROW(DSV dsv2 = dsv1);
}

TEST(DSVTest, can_assign_dsv)
{
    DSV dsv1(5);
    DSV dsv2(3);
    dsv1.unite(0, 1);
    ASSERT_NO_THROW(dsv2 = dsv1);
}

TEST(DSVTest, can_unite_multiple_elements) 
{
    DSV dsv(10);
    ASSERT_NO_THROW(dsv.unite(0, 1));
    ASSERT_NO_THROW(dsv.unite(1, 2));
    ASSERT_NO_THROW(dsv.unite(3, 4));
    ASSERT_NO_THROW(dsv.unite(2, 3));
}

TEST(DSVTest, can_handle_self_union)
{
    DSV dsv(5);
    ASSERT_NO_THROW(dsv.unite(2, 2));
}

TEST(DSVTest, can_create_large_dsv) 
{
    ASSERT_NO_THROW(DSV dsv(1000));
}

TEST(DSVTest, can_use_after_copy)
{
    DSV dsv1(5);
    dsv1.unite(0, 1);
    DSV dsv2 = dsv1;
    ASSERT_NO_THROW(DSV dsv2 = dsv1);
    ASSERT_NO_THROW(dsv2.find(0));
    ASSERT_NO_THROW(dsv2.connected(0, 1));
}
