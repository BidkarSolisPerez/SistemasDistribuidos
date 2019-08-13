/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

package org.apache.qpid.jms.test.testpeer.describedtypes;

import org.apache.qpid.jms.test.testpeer.ListDescribedType;
import org.apache.qpid.proton.amqp.Symbol;
import org.apache.qpid.proton.amqp.UnsignedLong;

/**
 * Generated by generate-described-types.xsl, which resides in this package.
 */
public class AttachFrame extends ListDescribedType
{
    public static final Symbol DESCRIPTOR_SYMBOL = Symbol.valueOf("amqp:attach:list");
    public static final UnsignedLong DESCRIPTOR_CODE = UnsignedLong.valueOf(0x0000000000000012L);


    private static final int FIELD_NAME = 0;
    private static final int FIELD_HANDLE = 1;
    private static final int FIELD_ROLE = 2;
    private static final int FIELD_SND_SETTLE_MODE = 3;
    private static final int FIELD_RCV_SETTLE_MODE = 4;
    private static final int FIELD_SOURCE = 5;
    private static final int FIELD_TARGET = 6;
    private static final int FIELD_UNSETTLED = 7;
    private static final int FIELD_INCOMPLETE_UNSETTLED = 8;
    private static final int FIELD_INITIAL_DELIVERY_COUNT = 9;
    private static final int FIELD_MAX_MESSAGE_SIZE = 10;
    private static final int FIELD_OFFERED_CAPABILITIES = 11;
    private static final int FIELD_DESIRED_CAPABILITIES = 12;
    private static final int FIELD_PROPERTIES = 13;

    public AttachFrame(Object... fields)
    {
        super(14);
        int i = 0;
        for(Object field : fields)
        {
            getFields()[i++] = field;
        }
    }

    @Override
    public Symbol getDescriptor()
    {
        return DESCRIPTOR_SYMBOL;
    }

    public AttachFrame setName(Object o)
    {
        getFields()[FIELD_NAME] = o;
        return this;
    }

    public AttachFrame setHandle(Object o)
    {
        getFields()[FIELD_HANDLE] = o;
        return this;
    }

    public AttachFrame setRole(Object o)
    {
        getFields()[FIELD_ROLE] = o;
        return this;
    }

    public AttachFrame setSndSettleMode(Object o)
    {
        getFields()[FIELD_SND_SETTLE_MODE] = o;
        return this;
    }

    public AttachFrame setRcvSettleMode(Object o)
    {
        getFields()[FIELD_RCV_SETTLE_MODE] = o;
        return this;
    }

    public AttachFrame setSource(Object o)
    {
        getFields()[FIELD_SOURCE] = o;
        return this;
    }

    public AttachFrame setTarget(Object o)
    {
        getFields()[FIELD_TARGET] = o;
        return this;
    }

    public AttachFrame setUnsettled(Object o)
    {
        getFields()[FIELD_UNSETTLED] = o;
        return this;
    }

    public AttachFrame setIncompleteUnsettled(Object o)
    {
        getFields()[FIELD_INCOMPLETE_UNSETTLED] = o;
        return this;
    }

    public AttachFrame setInitialDeliveryCount(Object o)
    {
        getFields()[FIELD_INITIAL_DELIVERY_COUNT] = o;
        return this;
    }

    public AttachFrame setMaxMessageSize(Object o)
    {
        getFields()[FIELD_MAX_MESSAGE_SIZE] = o;
        return this;
    }

    public AttachFrame setOfferedCapabilities(Object o)
    {
        getFields()[FIELD_OFFERED_CAPABILITIES] = o;
        return this;
    }

    public AttachFrame setDesiredCapabilities(Object o)
    {
        getFields()[FIELD_DESIRED_CAPABILITIES] = o;
        return this;
    }

    public AttachFrame setProperties(Object o)
    {
        getFields()[FIELD_PROPERTIES] = o;
        return this;
    }

}

