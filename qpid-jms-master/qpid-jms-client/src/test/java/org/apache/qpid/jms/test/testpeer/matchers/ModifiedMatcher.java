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

package org.apache.qpid.jms.test.testpeer.matchers;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.instanceOf;

import java.util.List;

import org.apache.qpid.proton.amqp.DescribedType;
import org.apache.qpid.proton.amqp.Symbol;
import org.apache.qpid.proton.amqp.UnsignedLong;
import org.apache.qpid.jms.test.testpeer.AbstractFieldAndDescriptorMatcher;
import org.hamcrest.Matcher;
import org.hamcrest.Description;
import org.hamcrest.TypeSafeMatcher;

/**
 * Generated by generate-matchers.xsl, which resides in this package.
 */
public class ModifiedMatcher extends TypeSafeMatcher<Object>
{
    private ModifiedMatcherCore coreMatcher = new ModifiedMatcherCore();
    private String mismatchTextAddition;
    private Object described;
    private Object descriptor;

    public ModifiedMatcher()
    {
    }

    @Override
    protected boolean matchesSafely(Object received)
    {
        try
        {
            assertThat(received, instanceOf(DescribedType.class));
            descriptor = ((DescribedType)received).getDescriptor();
            if(!coreMatcher.descriptorMatches(descriptor))
            {
                mismatchTextAddition = "Descriptor mismatch";
                return false;
            }

            described = ((DescribedType)received).getDescribed();
            assertThat(described, instanceOf(List.class));
            @SuppressWarnings("unchecked")
            List<Object> fields = (List<Object>) described;

            coreMatcher.verifyFields(fields);
        }
        catch (AssertionError ae)
        {
            mismatchTextAddition = "AssertionFailure: " + ae.getMessage();
            return false;
        }

        return true;
    }

    @Override
    protected void describeMismatchSafely(Object item, Description mismatchDescription)
    {
        mismatchDescription.appendText("\nActual form: ").appendValue(item);

        mismatchDescription.appendText("\nExpected descriptor: ")
                .appendValue(coreMatcher.getSymbolicDescriptor())
                .appendText(" / ")
                .appendValue(coreMatcher.getNumericDescriptor());

        if(mismatchTextAddition != null)
        {
            mismatchDescription.appendText("\nAdditional info: ").appendValue(mismatchTextAddition);
        }
    }

    public void describeTo(Description description)
    {
        description
            .appendText("Modified which matches: ")
            .appendValue(coreMatcher.getMatchers());
    }


    public ModifiedMatcher withDeliveryFailed(Matcher<?> m)
    {
        coreMatcher.withDeliveryFailed(m);
        return this;
    }

    public ModifiedMatcher withUndeliverableHere(Matcher<?> m)
    {
        coreMatcher.withUndeliverableHere(m);
        return this;
    }

    public ModifiedMatcher withMessageAnnotations(Matcher<?> m)
    {
        coreMatcher.withMessageAnnotations(m);
        return this;
    }

    public Object getReceivedDeliveryFailed()
    {
        return coreMatcher.getReceivedDeliveryFailed();
    }

    public Object getReceivedUndeliverableHere()
    {
        return coreMatcher.getReceivedUndeliverableHere();
    }

    public Object getReceivedMessageAnnotations()
    {
        return coreMatcher.getReceivedMessageAnnotations();
    }



    //Inner core matching class
    public static class ModifiedMatcherCore extends AbstractFieldAndDescriptorMatcher
    {
        /** Note that the ordinals of the Field enums match the order specified in the AMQP spec */
        public enum Field
        {
            DELIVERY_FAILED,
            UNDELIVERABLE_HERE,
            MESSAGE_ANNOTATIONS,
        }

        public ModifiedMatcherCore()
        {
            super(UnsignedLong.valueOf(0x0000000000000027L),
                  Symbol.valueOf("amqp:modified:list"));
        }


        public ModifiedMatcherCore withDeliveryFailed(Matcher<?> m)
        {
            getMatchers().put(Field.DELIVERY_FAILED, m);
            return this;
        }

        public ModifiedMatcherCore withUndeliverableHere(Matcher<?> m)
        {
            getMatchers().put(Field.UNDELIVERABLE_HERE, m);
            return this;
        }

        public ModifiedMatcherCore withMessageAnnotations(Matcher<?> m)
        {
            getMatchers().put(Field.MESSAGE_ANNOTATIONS, m);
            return this;
        }

        public Object getReceivedDeliveryFailed()
        {
            return getReceivedFields().get(Field.DELIVERY_FAILED);
        }

        public Object getReceivedUndeliverableHere()
        {
            return getReceivedFields().get(Field.UNDELIVERABLE_HERE);
        }

        public Object getReceivedMessageAnnotations()
        {
            return getReceivedFields().get(Field.MESSAGE_ANNOTATIONS);
        }

        @Override
        protected Enum<?> getField(int fieldIndex)
        {
            return Field.values()[fieldIndex];
        }
    }
}

