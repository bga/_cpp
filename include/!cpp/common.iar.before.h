/*
	Copyright 2020 Bga <bga.email@gmail.com>

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/


#pragma once

#if __IAR_SYSTEMS_ICC__ <= 8
	//# IAR 8 does not support { override }
	#define override
	#define final
	//# IAR 8 does not support { constexpr }
	#define BGA__MAYBE_CONSTEXPR

	#define BGA__CXX__NO_NULLPTR

	#define __ORDER_LITTLE_ENDIAN__ 0
	#define __ORDER_BIG_ENDIAN__ 1
	#if __LITTLE_ENDIAN__
		#define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__
	#else
		#define __BYTE_ORDER__ __ORDER_BIG_ENDIAN__
	#endif
#endif
#define __asm__ asm
